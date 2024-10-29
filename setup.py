from setuptools import setup, find_packages

setup(
    name='pj64memcompare',
    version='0.1.0',
    description='A package for comparing memory in Project64',
    author='Nayla Hanegan',
    author_email='naylahanegan@gmail.com',
    packages=find_packages(),
    install_requires=[
        'psutil',
    ],
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
    python_requires='>=3.6',
)