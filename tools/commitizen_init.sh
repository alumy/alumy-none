#!/bin/bash

# Please make sure that you already installed the npm in your system

# Please execute the next command to install commitizen for global by sudo user
# sudo npm install -g commitizen conventional-changelog-cli

commitizen init cz-conventional-changelog --force

npm install validate-commit-msg
npm install ghooks 

