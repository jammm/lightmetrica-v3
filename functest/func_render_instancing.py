# ---
# jupyter:
#   jupytext:
#     formats: ipynb,py:light
#     text_representation:
#       extension: .py
#       format_name: light
#       format_version: '1.3'
#       jupytext_version: 1.0.1
#   kernelspec:
#     display_name: Python 3
#     language: python
#     name: python3
# ---

# ## Rendering with instanced geometries
#
# This test demonstrates rendering with multi-level instancing.

# %load_ext autoreload
# %autoreload 2

import os
import imageio
import pandas as pd
import numpy as np
# %matplotlib inline
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
import lmfunctest as ft
import lmscene
import lightmetrica as lm

os.getpid()

# %load_ext lightmetrica_jupyter

lm.init()
lm.log.init('logger::jupyter', {})
lm.progress.init('progress::jupyter', {})

# +
# Create a sphere geometry with triangle mesh
r = 1
numTheta = 5
numPhi = 2*numTheta
vs = np.zeros((numPhi*(numTheta+1), 3))
ns = np.zeros((numPhi*(numTheta+1), 3))
ts = np.zeros((numPhi*(numTheta+1), 2))
for i in range(numTheta+1):
    for j in range(numPhi):
        theta = i*np.pi/numTheta
        phi = j*2*np.pi/numPhi
        idx = i*numPhi+j
        ns[idx,0] = np.sin(theta)*np.sin(phi)
        ns[idx,1] = np.cos(theta)
        ns[idx,2] = np.sin(theta)*np.cos(phi)
        vs[idx,0] = r*ns[idx,0]
        vs[idx,1] = r*ns[idx,1]
        vs[idx,2] = r*ns[idx,2]

fs = np.zeros((2*numPhi*(numTheta-1), 3), dtype=np.int32)
idx = 0
for i in range(1,numTheta+1):
    for j in range(1,numPhi+1):
        p00 = (i-1)*numPhi+j-1
        p01 = (i-1)*numPhi+j%numPhi
        p10 = i*numPhi+j-1
        p11 = i*numPhi+j%numPhi
        if i > 1:
            fs[idx,:] = np.array([p10,p01,p00])
            idx += 1
        if i < numTheta:
            fs[idx,:] = np.array([p11,p01,p10])
            idx += 1
# -

lm.asset('mesh_sphere', 'mesh::raw', {
    'ps': vs.flatten().tolist(),
    'ns': ns.flatten().tolist(),
    'ts': ts.flatten().tolist(),
    'fs': {
        'p': fs.flatten().tolist(),
        't': fs.flatten().tolist(),
        'n': fs.flatten().tolist()
    }
})


