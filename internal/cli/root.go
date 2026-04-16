package cli

import (
	"os"
	"github.com/spf13/cobra"
)

var rootCmd = &cobra.Command{
	Use:   "veloq [command] [flags]",
	Short: "The veloq cli",
	Long: `This is the veloq cli to control veloqd and run new commands, attach to running commands and replay logs`,
}

func Execute() {
	err := rootCmd.Execute()
	if err != nil {
		os.Exit(1)
	}
}

var verbose bool

func init() {
	rootCmd.PersistentFlags().BoolVarP(&verbose, "verbose", "v", false, "Enables verbose mode")
}