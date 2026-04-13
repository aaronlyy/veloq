function init()
  return {
    required = {"title", "name"}
  }
end

function main(input)
  local full_name = input.title .. " " .. input.name

  if input.name == "" then
    return {
      ok = false,
      message = "name is empty"
    }
  end

  return {
    ok = true,
    message = "hello " .. full_name
  }
end
