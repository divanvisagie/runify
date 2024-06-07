class Runify < Formula
  desc "Terminal client for Chat GPT"
  homepage "https://github.com/divanvisagie/runify"
  
  # Dynamically set the URL and SHA256 based on the CPU architecture
  if Hardware::CPU.intel?
    url "https://github.com/divanvisagie/runify/releases/download/{{tag}}/runify-darwin-x86_64.tar.gz"
    sha256 "{{intel_hash}}"
  elsif Hardware::CPU.arm?
    url "https://github.com/divanvisagie/runify/releases/download/{{tag}}/runify-darwin-aarch64.tar.gz"
    sha256 "{{arm_hash}}"
  else
    odie "Your architecture is not supported!"
  end

  def install
    bin.install "runify"
    man1.install "runify.1"
  end

  test do
    system "#{bin}/runify --version"
  end
end
