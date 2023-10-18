# Simple Shell C Programming Task

Project done by Mary Chukwu and Henry Akinola

This repository contains a basic implementation of a simple shell in the C programming language. The purpose of this project is to help you understand the fundamentals of how a shell works and to practice our C programming skills taught by ALX Africa. 

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [General Requirement](#general_requirement)
- [Compilation](#compilation)

## Introduction

A shell is a command-line interface that allows users to interact with an operating system by entering commands. This project implements a simplified version of a shell, demonstrating key concepts such as command parsing, execution, and basic error handling.

## Features

- Command parsing: Breaks user input into command and arguments.
- Basic execution: Executes commands using system calls.
- Error handling: Provides basic error messages for invalid commands.
- Simple interactive loop: Continuously prompts for user input and executes commands.

## General Requirement

All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89

All your files should end with a new line.

A README.md file, at the root of the folder of the project is mandatory.

Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl

All your header files should be include guarded.

## Compilation

Your shell will be compiled this way:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh