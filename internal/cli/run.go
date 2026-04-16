package cli

import (
	"fmt"
	"github.com/spf13/cobra"
)

var runCmd = &cobra.Command{
	Use:   "run",
	Short: "Run a command",
	Long: `This command runs a command, lol`,
	Run: func(cmd *cobra.Command, args []string) {
		
		if verbose {
			fmt.Println("verbose mode is enabled")
		}
		fmt.Println("run called")
	},
}

func init() {
	rootCmd.AddCommand(runCmd)
}
