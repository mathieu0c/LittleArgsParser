# LittleArgsParser

This is an awful implementation of a small parser for command line arguments. I tried to make it kinda generic and simple to use.

It is not really efficient and I am not even sure how this gets to work but it does.

<!--MARKDOWN_INDEX_BEGIN--># Table of content

**[LittleArgsParser](#littleargsparser)**<br/>
&emsp;*[Quick install](#quick-install)*<br/>
&emsp;&emsp;[Uninstall ](#uninstall)<br/>
&emsp;*[Build](#build)*<br/>
&emsp;&emsp;[Tests](#tests)<br/>
<!--MARKDOWN_INDEX_END-->

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

### Tests

And tests can be run using
```bash
cmake --build build -- test
```

One liner
```bash
cmake -Bbuild && cmake --build build && cmake --build build -- test
```