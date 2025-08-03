defmodule Mail do
	def get() do
		recieve do
			:Hello -> IO.puts "Hello"
			:World -> IO.puts "World"
			_ -> IO.puts "Huh?"
		end
	end
end

pid = spawn(&Mail.get/0)
send(pid, :World)
pid = spawn(&Mail.get/0)
send(pid, :Hello)
pid = spawn(&Mail.get/0)
send(pid,97)