#!/bin/bash -l

#SBATCH -D ./
#SBATCH -p course
#SBATCH -t 5

cores=${SLURM_CPUS_PER_TASK:-1}

export OMP_NUM_THREADS=$cores

gcc -march=native -O3 -fopenmp -fopt-info-vec matrices_weak.c -o matrices_weak.exe

./matrices_weak.exe