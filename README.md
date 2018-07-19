LegacyIONDRVSupport
=================

An IOKit driver to work with legacy Nvidia Tesla drivers on macOS 10.14.

### Features
- Provide missing `VSLGestalt()` function required by legacy Nvidia Tesla drivers.
- Works with patched Apple Nvidia Tesla drivers and/or Nvidia web drivers for macOS 10.13.

### Requirements
macOS 10.14 Mojave.

This kext is not fully tested. Use at your own risk.

### Background
Start with macOS 10.14, Apple removed drivers for legacy Nvidia GPUs not capable of running Metal. However these GPUs may still be usable with full hardware acceleration on macOS 10.14 by bringing back missing `_VSLGestalt()` symbol in IONDRVSupport, and also minor patches for the Tesla kexts. This kext would take care of the former by porting the original implementation from macOS 10.13 IOGraphics code.

Alternatively, you should be able to replace IOGraphicsFamily.kext and IONDRVSupport.kext with copies from macOS 10.13; Or use kext provided by [parrotgeek1](https://forums.macrumors.com/threads/macos-10-14-mojave-on-unsupported-macs-thread.2121473/page-60#post-26211398), which was built for similar purpose by adding the missing symbol.

### Usage
See [Usage](https://github.com/linzhouyu/LegacyIONDRVSupport/blob/master/Usage.md) page for more details about usage instructions.

### Changelog
#### v1.0.0
- Initial commit

### Credits
- [Apple](https://www.apple.com) for macOS
- [ASentientBot](https://forums.macrumors.com/threads/macos-10-14-mojave-on-unsupported-macs-thread.2121473/page-102#post-26239785) for the GeForceTeala binary patch
