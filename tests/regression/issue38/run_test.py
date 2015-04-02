import subprocess

def main ():
  if (os.name == "nt"):
    cmd = ["pin", "-t", "issue38.dll", "--", "./program"]
  else:
    cmd = ["pin", "-t", "libissue38.so", "--", "./program"]

  subprocess.check_call (cmd)

if __name__ == "__main__":
  main ()
