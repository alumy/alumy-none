#!/bin/bash

sudo npm install -g commitizen ghooks validate-commit-msg conventional-changelog-cli

commitizen init cz-conventional-changelog --save --save-exact

