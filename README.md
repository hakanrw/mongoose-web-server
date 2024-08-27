# mongoose-web-server

a web server written on C using the mongoose http library.

## support matrix

this project has been tested on following systems

- Linux (x86_64, i386, aarch64, armhf, riscv64, mips64el, sh4, alpha)
- Windows (x86_64, i386)
- FreeBSD (x86_64, aarch64)

## building
unix:
```sh
make
```

msvc (windows):
```cmd
msbuild
```

## running
unix:
```sh
make run
```

msvc (windows):
```cmd
msbuild /t:Run
```

## testing
unix:
```sh
make test
```

windows (msvc): test suite on windows not supported at this time.
