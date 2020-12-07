import torch
import torch.nn as nn
import torch.nn.functional as F

# 特征提取子网络
class Back(nn.Module):
    def __init__(self):
        super(Back,self).__init__()
        self.conv1=nn.Sequential(
            nn.Conv2d(3,96,11,2),
            nn.BatchNorm2d(96),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(3,2))
        self.conv2=nn.Sequential(
            nn.Conv2d(96,256,5,1,groups=2),
            nn.BatchNorm2d(256),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(3,2))
        self.conv3=nn.Sequential(
            nn.Conv2d(256,384,3,1),
            nn.BatchNorm2d(384),
            nn.ReLU(inplace=True))
        self.conv4=nn.Sequential(
            nn.Conv2d(384,384,3,1,groups=2),
            nn.BatchNorm2d(384),
            nn.ReLU(inplace=True))
        self.conv5=nn.Sequential(
            nn.Conv2d(384,256,3,1,groups=2))

    def forward(self,x):
        x=self.conv1(x)
        x=self.conv2(x)
        x=self.conv3(x)
        x=self.conv4(x)
        x=self.conv5(x)
        return x



