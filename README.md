# Install prerequisites

- Install ruby [version 3.1.x](https://rubyinstaller.org/downloads/)
- execute `gem install bundle`
- from folder `cucumber_wire_test` execute `bundle`

# Build recommendations

Using the VS Code reopen the project in the dev container, select the GCC x86 toolchain and build
inside the container
(Building on windows using MS Visual Studio 2017+ works as well)

# Executing tests

- From the containerd vscode terminal

```
    .\build\cucumber_wire_proxy\cucumber_test.cucumber_wire_proxy
```

- From the host system from cucumber_wire_test

```
    cucumber --format pretty --tag "@demo01"
    cucumber --format json --tag "@demo_b01"
```
