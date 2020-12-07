import torch
import torch.nn as nn
import torch.nn.functional as F

class Model(nn.Module):
    def __init__(self,back,head):
        self.back=back
        self.head=head

    def forward(self,z,x):
        z=self.back(z)
        x=self.back(x)
        return self.head(z,x)
