#!/bin/bash

sudo npm install -g commitizen conventional-changelog-cli

npm install --save-dev validate-commit-msg
npm install --save-dev ghooks 

commitizen init cz-conventional-changelog --save --save-exact

