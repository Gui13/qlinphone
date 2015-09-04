[![build status](http://ci.neolyse.info/projects/1/status.png?ref=master)](http://ci.neolyse.info/projects/1?ref=master)

## WARNING: This is not yet finished. I'm building this as a side project and hosting it in this incomplete state just because I want to.

A Qt UI for Linphone.

# Build


1. Install liblinphone on your computer.

    - Mac:
    
          brew tap Gui13/linphone
          brew install linphone

    - Ubuntu:
    
          sudo add-apt-repository ppa:linphone/release
          sudo aptitude update
          sudo aptitude install liblinphone-dev

    Other linuxes should be fine too, qlinphone requires linphone >= 3.8, just make sure you have that.

2. Install Qt Open Source somewhere, likely on your User directory

3. Run `qmake && make` in qlinphone's directory.