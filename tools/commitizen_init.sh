#!/bin/bash

# Please make sure that you already installed the npm in your system

# Please execute the next command to install commitizen for global
# sudo npm install -g commitizen conventional-changelog-cli

commitizen init cz-conventional-changelog --save --save-exact

npm install --save-dev validate-commit-msg
npm install --save-dev ghooks 

