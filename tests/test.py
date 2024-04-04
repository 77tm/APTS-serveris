import random

num_nodes = 1000
connections_per_node = 3  # Adjust this value to change the number of connections per node

# Open the file for writing
with open("test_graph.txt", "w") as f:
  # Write the number of nodes on the first line
  f.write(str(num_nodes) + "\n")

  # Generate connections randomly
  for node in range(num_nodes):
    for _ in range(connections_per_node):
      # Generate a random connection to another node (avoid self-loops)
      connected_node = random.randint(0, num_nodes - 1)
      if connected_node != node:
        f.write(f"{node} {connected_node}\n")

  # Write the end-of-file marker
  f.write("0 0\n")

print("Text file generated: test_graph.txt")
