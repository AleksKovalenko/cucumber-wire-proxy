# Install prerequisites

- Install ruby [version 3.1.x](https://rubyinstaller.org/downloads/)
- execute `gem install bundle`
- from folder `cucumber_test` execute `bundle`

# Build

```
    mkdir build && cd build && cmake ..
    make -j16
```

# Executing tests

- From the build dir run the cpp executable

```
    ./cucumber_wire_proxy/cucumber_test.cucumber_wire_proxy
```

- From top dir

```
    cucumber --format pretty --tag "@demo01"
    cucumber --format json --tag "@demo_b01"
```
