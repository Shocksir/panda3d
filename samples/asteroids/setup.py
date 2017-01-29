from direct.showutil.dist import *

setup(
    name="asteroids",
    options = {
        'build_p3d': {
            'directories': ['.'],
            'exclude_paths': ['build', 'setup.py', 'requirements.txt', 'wheels'],
            'gui_apps': {
                'asteroids': 'main.py',
            },
            'deploy_platforms': [
                'manylinux1_x86_64',
                'macosx_10_6_x86_64',
                'win32',
                'win_amd64',
            ],
        }
    }
)
