#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_os_ostream.h"

using namespace llvm;

static cl::opt<std::string> FileName(cl::Positional, cl::desc("Bitcode file"),
                                     cl::Required);

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "LLVM hello world\n");
  LLVMContext context;
  ErrorOr<std::unique_ptr<MemoryBuffer>> getFileResult =
      MemoryBuffer::getFile(FileName);
  if (getFileResult.getError()) {
    llvm::errs() << "Can't read file " << FileName << "\n";
    return -1;
  }
  std::unique_ptr<MemoryBuffer> &buffer = getFileResult.get();
  Expected<std::unique_ptr<Module>> parseResult =
      parseBitcodeFile(*buffer.get(), context);
  if (auto err = parseResult.takeError()) {
    llvm::errs() << "Error while processing the bitcode file\n";
    return -1;
  }
  std::unique_ptr<Module> &module = parseResult.get();
  for (Module::const_iterator i = module->getFunctionList().begin(),
                              e = module->getFunctionList().end();
       i != e; ++i) {
    if (!i->isDeclaration()) {
      llvm::outs() << i->getName() << " has " << i->size()
                   << " basic block(s).\n";
    }
  }
  return 0;
}
