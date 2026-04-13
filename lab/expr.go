package main

// https://expr-lang.org/docs/getting-started

import (
  "fmt"
  "github.com/expr-lang/expr"
  )

func main() {
  program, err := expr.Compile(`2 + 2`)
  if err != nil {
      panic(err)
  }

  output, err := expr.Run(program, nil)
  if err != nil {
      panic(err)
  }

  fmt.Print(output) // 4
}