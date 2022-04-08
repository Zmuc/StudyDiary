#!/usr/bin/env python
# -*- encoding: utf-8 -*-
# Salt自定义模块示例

# 虚拟模块名
__virtualname__ = 'mytest'

def __virtual__():
    return __virtualname__

def hello(obj):
    return "Hello " + obj

def ls():
    return __salt__['cmd.run']('ls -l')