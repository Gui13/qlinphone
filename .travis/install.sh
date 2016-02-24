#!/bin/bash


if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then

brew tap Gui13/linphone
brew install --head bellesip linphone 

else

sudo add-apt-repository -y ppa:linphone/release
sudo apt-add-repository -y ppa:beineri/opt-qt55
sudo apt-get update -qq
sudo apt-get install -y qt55quickcontrols qt55creator liblinphone-dev

fi


