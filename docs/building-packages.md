# Building Scylla Packages

This document describes how to build Scylla's packages for supported Linux distributions.

The build system generates _relocatable packages_, which means that the packages contain all the dependencies they need, and you can, therefore, install and run the same binaries on all Linux distributions.
The packages are built using Scylla's `dbuild` tool, which builds the packages in a Docker container.

## Building

The first step is to run `configure.py`, which generates the `build.ninja` file (equivalent of a `Makefile`):

```
./tools/toolchain/dbuild ./configure.py --mode=<mode>
```

(where `mode` is `release`, `dev`, or `debug`)

The second step is to build the packages with the `dist` target:

```
./tools/toolchain/dbuild ninja-build dist
```

## Artifacts

The `dist` target generates the following tarballs (*relocatable packages*), which can be installed on any Linux distribution:

* `build/<mode>/scylla-package.tar.gz`
* `build/release/scylla-python3-package.tar.gz`
* `scylla-jmx/build/scylla-jmx-package.tar.gz`
* `scylla-tools/build/scylla-tools-package.tar.gz`

The target also generates the following `.rpm` and `.deb` packages, which can be on any Fedora or Debian compatible distribution:

* `build/dist/<mode>/redhat/RPMS/x86_64/scylla-*.rpm`
* `build/dist/<mode>/redhat/RPMS/x86_64/scylla-conf-*.rpm`
* `build/dist/<mode>/redhat/RPMS/x86_64/scylla-debuginfo-*.rpm`
* `build/dist/<mode>/redhat/RPMS/x86_64/scylla-kernel-conf-*.rpm`
* `build/dist/<mode>/redhat/RPMS/x86_64/scylla-server-*.rpm`
* `build/redhat/RPMS/x86_64/scylla-python3-*.rpm`
* `scylla-jmx/build/redhat/RPMS/noarch/scylla-jmx-*.rpm`
* `scylla-tools/build/redhat/RPMS/noarch/scylla-tools-*.rpm`
* `scylla-tools/build/redhat/RPMS/noarch/scylla-tools-core-*.rpm`

## Verifying

To verify built Scylla packages, run the following command:

```
ninja-build dist-check
```

Please note that you need to run `dist-check` on the host because it
requires Docker to perform the verification.
