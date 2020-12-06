import torch
import torch.nn as nn
import torch.nn.functional as F

# 交叉相关子网络
class Head(nn.Module):
    def __init__(self,out_scale=0.001):
        self.out_scale=out_scale

    # 返回交叉相关结果
    def forward(self,z,x):
        return self.cross_correlation(z,x)*self.out_scale

    # 快速交叉相关
    def cross_correlation(self,z,x):
        nz=z.size(0)
        nx,c,h,w=x.size()
        x=x.view(-1,nz*c,h,w)
        out=F.conv2d(x,z,groups=nz)
        out=out.view(nx,-1,out.size(-2),out.size(-1))
        return out



