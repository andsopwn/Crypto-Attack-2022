# Crypto Attack 2022

This repository contains assorted experiments and example code for side-channel attacks against various block ciphers.

## Directory overview

- **AES/** – AES implementations and CPA examples in C.
- **ARIA/** – ARIA cipher implementations and attack code.
- **Alignment/** – Trace alignment utilities for preprocessing.
- **SEED/** – SEED cipher experiments and recovery code.
- **Second Order/** – programs used for second-order power analysis.
- **Template/** – Python scripts for template attacks.

Most programs are self-contained C sources that can be compiled with `gcc`. The Python scripts rely on `numpy` and `scipy`.
