package main

import (
	"fmt"
	"log"

	lua "github.com/yuin/gopher-lua"
)

type PluginMeta struct {
	Required []string
}

type PluginResult struct {
	OK      bool
	Message string
}

func main() {
	L := lua.NewState()
	defer L.Close()

	if err := L.DoFile("plugin.lua"); err != nil {
		log.Fatalf("failed to load plugin: %v", err)
	}

	meta, err := loadPluginMeta(L)
	if err != nil {
		log.Fatalf("invalid plugin init(): %v", err)
	}

	fmt.Println("required vars:", meta.Required)

	input := map[string]string{
		"title": "Dr.",
		"name":  "Aaron",
	}

	if missing := missingVars(meta.Required, input); len(missing) > 0 {
		log.Fatalf("missing required vars: %v", missing)
	}

	result, err := runPluginMain(L, input)
	if err != nil {
		log.Fatalf("invalid plugin main(): %v", err)
	}

	fmt.Printf("ok=%v message=%q\n", result.OK, result.Message)
}

func loadPluginMeta(L *lua.LState) (PluginMeta, error) {
	initFn := L.GetGlobal("init")
	if initFn.Type() != lua.LTFunction {
		return PluginMeta{}, fmt.Errorf("global init() function is required")
	}

	if err := L.CallByParam(lua.P{
		Fn:      initFn,
		NRet:    1,
		Protect: true,
	}); err != nil {
		return PluginMeta{}, err
	}

	ret := L.Get(-1)
	L.Pop(1)

	table, ok := ret.(*lua.LTable)
	if !ok {
		return PluginMeta{}, fmt.Errorf("init() must return a table")
	}

	requiredValue := table.RawGetString("required")
	requiredTable, ok := requiredValue.(*lua.LTable)
	if !ok {
		return PluginMeta{}, fmt.Errorf("init().required must be a table")
	}

	var required []string
	requiredTable.ForEach(func(_, value lua.LValue) {
		if value.Type() == lua.LTString {
			required = append(required, value.String())
		}
	})

	return PluginMeta{Required: required}, nil
}

func missingVars(required []string, input map[string]string) []string {
	var missing []string
	for _, key := range required {
		if _, ok := input[key]; !ok {
			missing = append(missing, key)
		}
	}
	return missing
}

func runPluginMain(L *lua.LState, input map[string]string) (PluginResult, error) {
	mainFn := L.GetGlobal("main")
	if mainFn.Type() != lua.LTFunction {
		return PluginResult{}, fmt.Errorf("global main() function is required")
	}

	arg := L.NewTable()
	for key, value := range input {
		arg.RawSetString(key, lua.LString(value))
	}

	if err := L.CallByParam(lua.P{
		Fn:      mainFn,
		NRet:    1,
		Protect: true,
	}, arg); err != nil {
		return PluginResult{}, err
	}

	ret := L.Get(-1)
	L.Pop(1)

	table, ok := ret.(*lua.LTable)
	if !ok {
		return PluginResult{}, fmt.Errorf("main() must return a table")
	}

	okValue := table.RawGetString("ok")
	messageValue := table.RawGetString("message")

	if okValue.Type() != lua.LTBool {
		return PluginResult{}, fmt.Errorf("main().ok must be a boolean")
	}
	if messageValue.Type() != lua.LTString {
		return PluginResult{}, fmt.Errorf("main().message must be a string")
	}

	return PluginResult{
		OK:      lua.LVAsBool(okValue),
		Message: messageValue.String(),
	}, nil
}
