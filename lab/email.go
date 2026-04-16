// this file demonstrates how to send emails using go-mail
// https://github.com/wneessen/go-mail/wiki/Getting-started

package main

import (
	"log"
	"github.com/wneessen/go-mail"
)

func send_mail() {
	// create new mail
	message := mail.NewMsg()

	// set the from field
	if err := message.From("hey@krotesq.com"); err != nil {
		log.Fatalf("failed to set From address: %s", err)
	}


	// the the to field
	if err := message.To("tina.recipient@example.com"); err != nil {
		log.Fatalf("failed to set To address: %s", err)
	}

	// now we set the subject and the message
	message.Subject("This is a test mail")
	message.SetBodyString(mail.TypeTextPlain, "Wow an E-Mail!")


	// now we define a smtp client to handle the sending
	client, err := mail.NewClient("localhost", mail.WithPort(1025), mail.WithTLSPolicy(mail.NoTLS))

	if err != nil {
		log.Fatalf("failed to create smtp client %s", err)
	}

	// now we send the mail
	if err := client.DialAndSend(message); err != nil {
		log.Fatalf("error sending mail %s", err)
	}
}