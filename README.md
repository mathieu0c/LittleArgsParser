# LittleArgsParser

This is an awful implementation of a small parser for command line arguments. I tried to make it kinda generic and simple to use.

It is not really efficient and I am not even sure how this gets to work but it does.

## Quick install

```bash
cd libLittleArgsParser
cmake -Bbuild && cmake --build build && sudo cmake --build build -- install
```

### Uninstall 

```bash
cd libLittleArgsParser/build
xargs rm < install_manifest.txt
```

## Build

```bash
cd libLittleArgsParser
cmake -Bbuild
cmake --build build
```

And tests can be run using
```bash
cmake --build build -- test
```

One liner
```bash
cmake -Bbuild && cmake --build build -- test
```