from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

# add pca9685 src files.
if GetDepend('PKG_USING_PCA9685'):
    src += Glob('pca9685.c')

if GetDepend('PKG_USING_PCA9685_SAMPLE'):
    src += Glob('pca9685_sample.c')

# add pca9685 include path.
path  = [cwd]

# add src and include to group.
group = DefineGroup('pca9685', src, depend = ['PKG_USING_PCA9685'], CPPPATH = path)

Return('group')
