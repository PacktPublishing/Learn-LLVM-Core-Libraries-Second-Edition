#include "llvm/Support/Error.h"
#include <fstream>
#include <iostream>
using namespace llvm;

// User-defined ErrorInfo.
class FileNotFound : public ErrorInfo<FileNotFound> {
public:
  inline static char ID;
  std::string Path;

  FileNotFound(StringRef Path) : Path(Path.str()) {}
  void log(raw_ostream &OS) const override { OS << Path << " is not found\n"; }
  std::error_code convertToErrorCode() const override {
    return std::make_error_code(std::io_errc::stream);
  }
};

class CantCreateFile : public ErrorInfo<CantCreateFile> {
public:
  inline static char ID;
  std::string Path;

  CantCreateFile(StringRef Path) : Path(Path.str()) {}
  void log(raw_ostream &OS) const override { OS << Path << " is not found\n"; }
  std::error_code convertToErrorCode() const override {
    return std::make_error_code(std::io_errc::stream);
  }
};

Expected<bool> substitute(StringRef input, StringRef output, int var) {
  std::ifstream inStream(input.data());
  if (!inStream.is_open())
    return make_error<FileNotFound>(input);
  std::string data;
  getline(inStream, data);
  size_t index = data.find("$var");
  llvm::outs() << data << " @ " << index << "\n";
  if (index == std::string::npos)
    return false;
  data.replace(index, 4, std::to_string(var));
  std::ofstream outStream(output.data());
  if (!outStream.is_open())
    return make_error<CantCreateFile>(output);
  outStream << data;
  return true;
}

int main() {
  auto Result = substitute("in.txt", "out.txt", 42);
  // Error handling
  if (Error Err = Result.takeError()) {
    handleAllErrors(std::move(Err),
                    [](const FileNotFound &FNF) { FNF.log(llvm::errs()); },
                    [](const CantCreateFile &CCF) { CCF.log(llvm::errs()); });
    return 1;
  }
  return !(*Result);
}
