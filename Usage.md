LegacyIONDRVSupport Usage
=======================

### Installation
The prebuilt binaries are available on [releases](https://github.com/linzhouyu/LegacyIONDRVSupport/releases) page.

Install the kext to `/Library/Extensions/`, verify permissions and rebuild kernel cache.

This is an unsigned kext, to load it you will first need to disable kext signing check in Recovery OS. In order to work with modified Nvidia Tesla kexts, filesystem protection may needs to be disabled as well.    
`csrutil enable --without kext --without fs`

### Patch Nvidia Tesla drivers
1. Add additional dependency for `NVDAResmanTesla(Web).kext`
```xml
<!--File: NVDAResmanTesla(Web).kext\Contents\Info.plist-->
<key>OSBundleLibraries</key>
<dict>
<key>xyz.linuslin.iokit.LegacyIONDRVSupport</key>
<string>1.0.0</string> 
</dict>
```
2. Binary patch `GeForceTesla(Web).kext` to prevent random panic.
```
// File: GeForceTesla(Web).kext\Contents\MacOS\GeForceTesla(Web)
Find
488B07FF90C00000
Replace
488B07660F1F4400
```
3. (Optional) Correct system build version in `NVDAStartupWeb.kext` if use web driver.
This could be done by using [nvidia-update](https://github.com/Benjamin-Dobell/nvidia-update) script.

#### Recommanded kexts install location
- /Library/Extensions/ 
```
LegacyIONDRVSupport.kext
GeForceTesla(Web).kext
NVDANV50HalTesla(Web).kext
NVDAResmanTesla(Web).kext
````
- /System/Library/Extensions/
```
GeForceTeslaGLDriver(Web).bundle
GeForceTeslaVADriver(Web).bundle
GeForceTeslaGAWeb.bundle
```

### Credits
- [ASentientBot](https://forums.macrumors.com/threads/macos-10-14-mojave-on-unsupported-macs-thread.2121473/page-102#post-26239785) for original GeForceTeala binary patch
