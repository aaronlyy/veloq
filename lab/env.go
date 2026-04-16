package main

// how to read env vars and dotenv vars in go

import (
	"github.com/joho/godotenv"
	"log"
	"os"
)

func load_dot_env() {
	err := godotenv.Load()
	if err != nil {
		log.Fatalf("error loading .env file: %s\n", err)
	}
	foo := os.Getenv("FOO")
	log.Printf("FOO: %s\n", foo)
}