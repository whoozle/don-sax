# QMLOL: QML Object Notation specification and reference implementation

Sax style parser

## Motivation

Simplier and cleaner language for declaring structures of platform-independent abstract data, similar to JSON. 

## Simple Examples
```
//simple example and c-style comment
Build {
  Directory {
    name: 'src'; readable: true; scan: true
  }
  Target {
    name: 'test':
    sources: [null, false, true, 1, 2.45e-38, 'string', { /*plain json object*/ }, Target { /*named object is fine too*/ } ]
  }
  effect: Effect { shadow: 1 }
}
```
