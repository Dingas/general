defmodule Mail do
	def get() do
		recieve do
			:Hello -> IO.puts "Hello"
			:World -> IO.puts "World"

		end
	end
end

pid = spawn(&Mail.get/0)
send(pid, :World)
pid = spawn(&Mail.get/0)
send(pid, :Hello)
