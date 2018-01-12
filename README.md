# JSON with classes: Javascript Object Notation with Classes
Specification and reference implementation of sax style parser

## Motivation

Simplier and cleaner language for declaring structures of platform-independent abstract data, similar to JSON. 

## Simple Examples
```json
//simple example and c-style comment
Build {

  dir: Directory {
    name: 'src'; readable: true; scan: true
  },

  target: Target {
    name: 'test';
    sources: [null, false, true, 1, 2.45e-38, 'string', { /*plain json object*/ }, Target { /*named object is fine too*/ } ]
  },

  effect: Effect { 'shadow': 1 } //json-style properties are fine too
}
```
