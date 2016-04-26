stub = 'fake'
filenames_2 = (
    stub + '_s.dat',
    stub + '_t.dat',
    stub + '_v.dat',
)
filenames_4 = (
    stub + '_eri.dat',
)
dim = 150

from random import random

indices = list(range(dim))

for filename_2 in filenames_2:
    with open(filename_2, 'w') as fh:
        for i in indices:
            for j in indices[:i+1]:
                fh.write(' {} {} {}\n'.format(i+1, j+1, random()))

for filename_4 in filenames_4:
    with open(filename_4, 'w') as fh:
        for i in indices:
            for j in indices[:i+1]:
                for k in indices[:j]:
                    for l in indices[:k]:
                        fh.write(' {} {} {} {} {}\n'.format(i+1, j+1, k+1, l+1, random()))
