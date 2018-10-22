// Mark conditions for MC/DC computation 13th Aug 2018 3:20 PM
//
// Copyright 2017 National University of Singapore
// See LICENSE.md for the license information.

#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/SourceMgr.h"

#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
using namespace std;
#include <string>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "llvm-c/TargetMachine.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constants.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm-c/BitWriter.h"
//#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/MemoryBuffer.h"

#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string

#define DEBUG 0

/*
 * Main.
 */
int main(int argc, char **argv) {

	std::string sequenceFile = "";
	if (argc < 2) {
		llvm::errs() << "Filename unspecified\n";
		return 1;
	} else {
		sequenceFile = argv[2];
	}
	if (DEBUG > 0)
		llvm::errs() << "sequenceFile:" << sequenceFile << "\n";

	llvm::LLVMContext &Context = llvm::getGlobalContext();
	llvm::SMDiagnostic Err;
	llvm::Module *M = ParseIRFile(argv[1], Err, Context);

	if (M == 0) {
		llvm::errs() << "ERROR: failed to load " << argv[0] << "\n";
		return 1;
	}
	if (DEBUG > 0)
		llvm::errs() << "Benchmark:" << argv[1] << "\n";

	//=====================================================================
	// Code to open a file and read the truth values for sequences created.
	//=====================================================================
	int KappaValue = 0;
	int labelTag = 0;

	int truthvalue;
	int conditionvalue[100000];
	int icmpp[100000];
	// char a;
	int i = 0, j = 0, count = 0, counttruth = 0, FLAG = 0;
	string line;
	int seqLength = 0;

	ifstream myfile(sequenceFile, ios_base::in);
	// std::fstream myfile("seq.txt", std::ios_base::in);
	bool firstNonDontCareSeen = 0;
	if (myfile.is_open()) {
		if (myfile >> truthvalue) {
			seqLength = truthvalue;
		}
		while (myfile >> truthvalue) {
			icmpp[i] = truthvalue; // Assigning the truth values from the seq.txt
								   // files in a comparison array to check the truth
								   // and false value
			if ((truthvalue == 1) || (truthvalue == 0)) {
				if (firstNonDontCareSeen == 0) {
					seqLength = seqLength + i - 1;
					firstNonDontCareSeen = 1;
				}
				count++;
			}
			if (DEBUG > 0)
				llvm::errs() << "The value of truthvalue = " << truthvalue
						<< "\n";
			i++;
		}
		myfile.close();
	} else {
		cout << "Unable to open file";
	}

	int size_of_icmpp = i; //Because in while loop we changed the syntax //remove
	int icmp = 0;
	llvm::GlobalVariable *kappa;
	//for (auto &F : *M) {
	for (llvm::Module::global_iterator GI = M->global_begin(), GE =
			M->global_end(); GI != GE; ++GI) {
		if (GI->getName() == "kappa") {
			if (DEBUG > 0)
				GI->dump();
			kappa = GI;
		}
	}

	//=====================================================================
	// Main Loop - Running over BBs
	//=====================================================================
	for (auto &F : *M) {
		for (llvm::Function::iterator b = F.begin(); b != F.end(); ++b) {
			for (llvm::BasicBlock::iterator ins = b->begin(); ins != b->end();
					++ins) {
				if (llvm::isa<llvm::ICmpInst>(ins) && icmp < size_of_icmpp) {
					if (DEBUG > 0)
						llvm::errs() << "condition number \n" << icmp << "\n";
					if (DEBUG > 0)
						llvm::errs() << "size_of_icmpp:" << size_of_icmpp
								<< "\n";
					if (DEBUG > 0)
						llvm::errs() << *ins << "\n";
					if (DEBUG > 0)
						llvm::errs() << icmpp[icmp] << "\n";
					llvm::BranchInst *bi = llvm::dyn_cast<llvm::BranchInst>(
							ins->getNextNode());
					if (bi->getNumOperands() == 3) {

						switch (icmpp[icmp]) {
						case 0: {
							// False Case
							counttruth++;
							KappaValue = (KappaValue * 10) + 2;

							// Reading the False Edge of BR
							std::string buf;
							llvm::raw_string_ostream stream(buf);
							bi->getOperand(1)->print(stream);
							stream.flush();

							// Gettig the label name of False Edge of BR
							size_t predPos = buf.find("pred");
							std::string label = buf.substr(0, predPos);
							if (DEBUG > 0)
								llvm::errs() << "LABEL:" << label << "\n";

							// Creating the IR
							llvm::IRBuilder<> IR(
									llvm::dyn_cast<llvm::BasicBlock>(
											bi->getOperand(1)));

							//inserting the store instruction for kappa variable
							if (counttruth == 1) {
								llvm::IRBuilder<> builder1(ins); // ins is for creating store instruction kappa = 0 in before icmp
								llvm::StoreInst *Store_zero =
										builder1.CreateStore(IR.getInt32(0),
												kappa);
							}

							// Reterieving destination block
							llvm::BasicBlock *tempblock;
							tempblock = llvm::dyn_cast<llvm::BasicBlock>(
									bi->getOperand(1));

							llvm::BasicBlock *previousBB;
							llvm::BasicBlock *nextNextBB;
							if (label.find("kappa") != std::string::npos) {
								//KAPPA Annotation Already Done.
								llvm::BasicBlock *nextBB = llvm::dyn_cast<
										llvm::BasicBlock>(bi->getOperand(1));
								llvm::BranchInst *NextBBBranch = llvm::dyn_cast<
										llvm::BranchInst>(&nextBB->back());
								nextNextBB = llvm::dyn_cast<llvm::BasicBlock>(
										NextBBBranch->getOperand(0));
								previousBB = llvm::dyn_cast<llvm::BasicBlock>(
										bi->getOperand(1));

							} else {
								//KAPPA Annotation Should be Done.

								// Creating middle basic block for kappa increment
								std::ostringstream oss;
								oss << labelTag++;
								std::string newLabel = "kappa_";
								newLabel += oss.str();
								oss.flush();

								llvm::BasicBlock *newblock =
										llvm::BasicBlock::Create(
												llvm::getGlobalContext(),
												newLabel, &F);
								llvm::IRBuilder<> builder(newblock);
								llvm::LoadInst *Load = builder.CreateLoad(
										kappa);
								llvm::Value *Inc = builder.CreateMul(
										IR.getInt32(10), Load);
								llvm::StoreInst *Store = builder.CreateStore(
										Inc, kappa);
								llvm::LoadInst *Load1 = builder.CreateLoad(
										kappa);
								llvm::Value *Inc1 = builder.CreateAdd(
										IR.getInt32(2), Load1);
								llvm::StoreInst *Store1 = builder.CreateStore(
										Inc1, kappa);

								// Handling Don't Care Case and inserting the BR in the end of BB
								if (icmpp[icmp + 1] != 9) {
									llvm::BranchInst *Br = builder.CreateBr(
											tempblock);
								} else {
									int z = icmp + 1;
									while (icmpp[z] == 9 && z <= seqLength) {
										llvm::LoadInst *Load =
												builder.CreateLoad(kappa);
										llvm::Value *Inc = builder.CreateMul(
												IR.getInt32(10), Load);
										llvm::StoreInst *Store =
												builder.CreateStore(Inc, kappa);
										z++;
									}
									llvm::BranchInst *Br = builder.CreateBr(
											tempblock);
								}

								// Point current basic block to the newly created block
								llvm::BranchInst *newBr =
										llvm::BranchInst::Create(
												llvm::dyn_cast<llvm::BasicBlock>(
														bi->getOperand(2)),
												newblock, bi->getCondition());
								b->getInstList().insertAfter(bi,
										llvm::dyn_cast<llvm::Instruction>(
												newBr));
								bi->removeFromParent();
								previousBB = newblock;
								llvm::BranchInst *NextBBBranch = llvm::dyn_cast<
										llvm::BranchInst>(&newblock->back());
								nextNextBB = llvm::dyn_cast<llvm::BasicBlock>(
										NextBBBranch->getOperand(0));
							}

							if (counttruth == count) {
								// Since this is the last insertion, the Kappa value should be updated before inserting
								// the assert BB
								for (int z = icmp; z <= seqLength; z++)
									if (icmpp[z] == 9)
										KappaValue = (KappaValue * 10);

								//new fail basic block
								llvm::BasicBlock *fail =
										llvm::BasicBlock::Create(
												llvm::getGlobalContext(),
												"fail", &F);
								llvm::IRBuilder<> builder2(fail);
								//begin of klee_assert
								llvm::Constant *c = M->getOrInsertFunction(
										"__assert_fail",
										llvm::FunctionType::getVoidTy(
												F.getContext()),
										llvm::Type::getInt8PtrTy(
												F.getContext()),
										llvm::Type::getInt8PtrTy(
												F.getContext()),
										llvm::IntegerType::get(
												llvm::getGlobalContext(), 32),
										llvm::Type::getInt8PtrTy(
												F.getContext()),
										NULL);
								llvm::Function *assert_fail = llvm::dyn_cast<
										llvm::Function>(c);
								std::ostringstream ossMsg;
								ossMsg << KappaValue;
								//std::string ossMsg = std::to_string(KappaValue);
								std::string msgString = "kappa violation ";
								//msgString += ossMsg;
								msgString += ossMsg.str();
								
								
								
								ossMsg.flush();
								llvm::Value *message =
										builder2.CreateGlobalStringPtr(
												msgString, ".str");
								llvm::Value *file =
										builder2.CreateGlobalStringPtr("",
												".str");
								llvm::ConstantInt *line = builder2.getInt32(0);
								llvm::Value *function =
										builder2.CreateGlobalStringPtr("main",
												".str");
								builder2.CreateCall4(assert_fail, message, file,
										line, function);
								llvm::BranchInst *Br2 = builder2.CreateBr(
										llvm::dyn_cast<llvm::BasicBlock>(nextNextBB));
//								llvm::ReturnInst *retValue = builder2.CreateRet(
//										IR.getInt32(-1));

								//inserting the klee_assert instructions
								llvm::BasicBlock *assert =
										llvm::BasicBlock::Create(
												llvm::getGlobalContext(),
												"assert", &F);
								llvm::IRBuilder<> builder3(assert);
								llvm::LoadInst *Load33 = builder3.CreateLoad(
										kappa);
								llvm::Value *kappacheck = builder3.CreateICmpNE(
										Load33, IR.getInt32(KappaValue), "tmp");
								llvm::BranchInst *kappaBr =
										builder3.CreateCondBr(kappacheck,
												llvm::dyn_cast<llvm::BasicBlock>(
														nextNextBB), fail);

								//Updating the Kappa Annotation Outgoing Edge
								llvm::IRBuilder<> builder4(previousBB);
								previousBB->getInstList().back().removeFromParent();
								//b->getInstList().insertAfter(bi,llvm::dyn_cast<llvm::Instruction>(newBr));
								llvm::BranchInst *Br = builder4.CreateBr(
										assert);
							}
							break;
						}

						case 1: {
							// True Case
							counttruth++;
							KappaValue = (KappaValue * 10) + 1;

							// Reading the True Edge of BR
							std::string buf;
							llvm::raw_string_ostream stream(buf);
							bi->getOperand(2)->print(stream);
							stream.flush();

							// Gettig the label name of True Edge of BR
							size_t predPos = buf.find("pred");
							std::string label = buf.substr(0, predPos);
							if (DEBUG > 0)
								llvm::errs() << "LABEL:" << label << "\n";

							// Creating the IR
							llvm::IRBuilder<> IR(
									llvm::dyn_cast<llvm::BasicBlock>(
											bi->getOperand(2)));

							//inserting the store instruction for kappa variable
							if (counttruth == 1) {
								llvm::IRBuilder<> builder1(ins); // ins is for creating store instruction kappa = 0 in before icmp
								llvm::StoreInst *Store_zero =
										builder1.CreateStore(IR.getInt32(0),
												kappa);
							}

							// Reterieving destination block
							llvm::BasicBlock *tempblock;
							tempblock = llvm::dyn_cast<llvm::BasicBlock>(
									bi->getOperand(2));

							llvm::BasicBlock *previousBB;
							llvm::BasicBlock *nextNextBB;
							if (label.find("kappa") != std::string::npos) {
								//KAPPA Annotation Already Done.
								llvm::BasicBlock *nextBB = llvm::dyn_cast<
										llvm::BasicBlock>(bi->getOperand(2));
								llvm::BranchInst *NextBBBranch = llvm::dyn_cast<
										llvm::BranchInst>(&nextBB->back());
								nextNextBB = llvm::dyn_cast<llvm::BasicBlock>(
										NextBBBranch->getOperand(0));
								previousBB = llvm::dyn_cast<llvm::BasicBlock>(
										bi->getOperand(2));
							} else {
								//KAPPA Annotation Should be Done.
								// Creating middle basic block for kappa increment
								std::ostringstream oss;
								oss << labelTag++;
								std::string newLabel = "kappa_";
								newLabel += oss.str();
								oss.flush();

								llvm::BasicBlock *newblock =
										llvm::BasicBlock::Create(
												llvm::getGlobalContext(),
												newLabel, &F);
								llvm::IRBuilder<> builder(newblock);
								llvm::LoadInst *Load = builder.CreateLoad(
										kappa);
								llvm::Value *Inc = builder.CreateMul(
										IR.getInt32(10), Load);
								llvm::StoreInst *Store = builder.CreateStore(
										Inc, kappa);
								llvm::LoadInst *Load1 = builder.CreateLoad(
										kappa);
								llvm::Value *Inc1 = builder.CreateAdd(
										IR.getInt32(1), Load1);
								llvm::StoreInst *Store1 = builder.CreateStore(
										Inc1, kappa);

								// Handling Don't Care Case and inserting the BR in the end of BB
								if (icmpp[icmp + 1] != 9) {
									llvm::BranchInst *Br = builder.CreateBr(
											tempblock);
								} else {
									int z = icmp + 1;
									while (icmpp[z] == 9 && z <= seqLength) {
										llvm::LoadInst *Load =
												builder.CreateLoad(kappa);
										llvm::Value *Inc = builder.CreateMul(
												IR.getInt32(10), Load);
										llvm::StoreInst *Store =
												builder.CreateStore(Inc, kappa);
										z++;
									}
									llvm::BranchInst *Br = builder.CreateBr(
											tempblock);
								}

								// Point current basic block to the newly created block
								llvm::BranchInst *newBr =
										llvm::BranchInst::Create(newblock,
												llvm::dyn_cast<llvm::BasicBlock>(
														bi->getOperand(1)),
												bi->getCondition());
								b->getInstList().insertAfter(bi,
										llvm::dyn_cast<llvm::Instruction>(
												newBr));
								bi->removeFromParent();
								previousBB = newblock;
								llvm::BranchInst *NextBBBranch = llvm::dyn_cast<
										llvm::BranchInst>(&newblock->back());
								nextNextBB = llvm::dyn_cast<llvm::BasicBlock>(
										NextBBBranch->getOperand(0));
							}

							if (counttruth == count) {
								// Since this is the last insertion, the Kappa value should be updated before inserting
								// the assert BB
								//for (int x=7;x>icmp;x--)
								for (int z = icmp; z <= seqLength; z++)
									if (icmpp[z] == 9)
										KappaValue = (KappaValue * 10);

								//new fail basic block
								llvm::BasicBlock *fail =
										llvm::BasicBlock::Create(
												llvm::getGlobalContext(),
												"fail", &F);
								llvm::IRBuilder<> builder2(fail);
								//begin of klee_assert
								llvm::Constant *c = M->getOrInsertFunction(
										"__assert_fail",
										llvm::FunctionType::getVoidTy(
												F.getContext()),
										llvm::Type::getInt8PtrTy(
												F.getContext()),
										llvm::Type::getInt8PtrTy(
												F.getContext()),
										llvm::IntegerType::get(
												llvm::getGlobalContext(), 32),
										llvm::Type::getInt8PtrTy(
												F.getContext()),
										NULL);
								llvm::Function *assert_fail = llvm::dyn_cast<
										llvm::Function>(c);
								std::ostringstream ossMsg;
								ossMsg << KappaValue;
								//std::string ossMsg = std::to_string(KappaValue);
								std::string msgString = "kappa violation ";
								msgString += ossMsg.str();
								//msgString += ossMsg;
								ossMsg.flush();
								llvm::Value *message =
										builder2.CreateGlobalStringPtr(
												msgString, ".str");
								llvm::Value *file =
										builder2.CreateGlobalStringPtr("",
												".str");
								llvm::ConstantInt *line = builder2.getInt32(0);
								llvm::Value *function =
										builder2.CreateGlobalStringPtr("main",
												".str");
								builder2.CreateCall4(assert_fail, message, file,
										line, function);
								llvm::BranchInst *Br2 = builder2.CreateBr(
										llvm::dyn_cast<llvm::BasicBlock>(nextNextBB));
//								llvm::ReturnInst *retValue = builder2.CreateRet(
//										IR.getInt32(-1));

								//inserting the klee_assert instructions
								llvm::BasicBlock *assert =
										llvm::BasicBlock::Create(
												llvm::getGlobalContext(),
												"assert", &F);
								llvm::IRBuilder<> builder3(assert);
								llvm::LoadInst *Load33 = builder3.CreateLoad(
										kappa);
								llvm::Value *kappacheck = builder3.CreateICmpNE(
										Load33, IR.getInt32(KappaValue), "tmp");
								llvm::BranchInst *kappaBr =
										builder3.CreateCondBr(kappacheck,
												llvm::dyn_cast<llvm::BasicBlock>(
														nextNextBB), fail);

								//Updating the Kappa Annotation Outgoing Edge
								llvm::IRBuilder<> builder4(previousBB);
								previousBB->getInstList().back().removeFromParent();
								//b->getInstList().insertAfter(bi,llvm::dyn_cast<llvm::Instruction>(newBr));
								llvm::BranchInst *Br = builder4.CreateBr(
										assert);
							}

							break;
						}
						case 9: {
							//if((icmpp[icmp-1] != 1) || (icmpp[icmp-1] != 0)) //In case 0: and case 1: we have done some logic form Kappavalue Uncomment later
							KappaValue = (KappaValue * 10);
							if (DEBUG > 0)
								llvm::errs()
										<< "Don't care case annotation is already done.\n ";

							break;
						}

						default: {
							llvm::errs()
									<< "Wrong code in sequence. It should be either 0,1 or 9.";
							break;
						}

						}
						icmp++;
					}
				}
			}
		}
	}

	//=====================================================================
	// Dumping Updated Module
	//=====================================================================
	// TODO: Uncomment Later
	llvm::outs() << *M;
	return 0;
}

//

//  std::size_t s = buf.find('\n');

/*if (s != std::string::npos) {
 if (s == 0) {
 buf = buf.substr(1, buf.size() - 1);
 s = buf.find('\n');
 if (s != std::string::npos) {
 std::string label = buf.substr(0, s);
 llvm::errs() << "FIRST BRANCH: " << label << "\n";

 //inserting the store instruction for kappa variable
 if(counttruth == 1)
 {
 llvm::IRBuilder<> builder1(ins); // ins is for creating store instruction kappa = 0 in before icmp
 llvm::StoreInst *Store_zero = builder1.CreateStore(IR.getInt32(0), kappa);
 }

 // Reterieving destination block
 llvm::BasicBlock *tempblock;
 tempblock = llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(2));


 //here I need to focus
 // Add instructions to the new block
 //to chck the new idea or else disable it
 //                            llvm::LoadInst *Load = builder.CreateLoad(kappa);
 //                            llvm::Value *Inc = builder.CreateMul(IR.getInt32(10), Load);
 //                            llvm::StoreInst *Store = builder.CreateStore(Inc, kappa);
 //                            llvm::LoadInst *Load1 = builder.CreateLoad(kappa);
 //                            llvm::Value *Inc1 = builder.CreateAdd(IR.getInt32(1), Load1);
 //                            llvm::StoreInst *Store1 = builder.CreateStore(Inc1, kappa);
 //                            llvm::BranchInst *Br = builder.CreateBr(tempblock);


 llvm::errs() << "here we are for TRUE" << label << "up to here for TRUE";

 size_t predPos = label.find("pred");
 label = label.substr( 0, predPos );
 llvm::errs() << "LABEL:" << label << "\n";
 if(label.find("kappa") == std::string::npos)
 {

 //                                if(icmpp[icmp+1]!=9)
 //                                {
 //				llvm::BranchInst *Br = builder.CreateBr(assert);
 //                                }
 //                                else
 //                                {
 //                                llvm::BranchInst *Br = builder.CreateBr(tempblock);
 //                                }


 //In case of DC just update KappaValue
 //KappaValue = KappaValue * 10 + 0; // True


 if(icmpp[icmp+1]!=9 && counttruth != count)
 {

 }
 else if(icmpp[icmp+1]!=9 && counttruth == count) //enable it later
 {   //inserting the klee_assert instructions
 llvm::BasicBlock *assert = llvm::BasicBlock::Create(
 llvm::getGlobalContext(),"assert" , &F);
 llvm::BranchInst *Br = builder.CreateBr(assert);
 //new fail basic block
 llvm::BasicBlock *fail = llvm::BasicBlock::Create(
 llvm::getGlobalContext(),"fail" , &F);
 llvm::IRBuilder<> builder2(fail);
 //begin of klee_assert
 llvm::Constant *c = M->getOrInsertFunction("__assert_fail",
 llvm::FunctionType::getVoidTy(F.getContext()),
 llvm::Type::getInt8PtrTy(F.getContext()),
 llvm::Type::getInt8PtrTy(F.getContext()),
 llvm::IntegerType::get(llvm::getGlobalContext(),32),
 llvm::Type::getInt8PtrTy(F.getContext()),
 NULL);
 llvm::Function *assert_fail = llvm::dyn_cast<llvm::Function>(c);
 //IRBuilder<> builder(inst);
 llvm::Value *message = builder2.CreateGlobalStringPtr("kappa violation", ".str");
 llvm::Value *file = builder2.CreateGlobalStringPtr("", ".str");
 llvm::ConstantInt *line = builder2.getInt32(0);
 llvm::Value *function = builder2.CreateGlobalStringPtr("main", ".str");
 builder2.CreateCall4(assert_fail,message,file,line,function);
 //end of klee_assert

 llvm::ReturnInst *retValue = builder2.CreateRet(IR.getInt32(-1));

 //llvm::BranchInst *emptyBr = builder2.CreateBr(
 //        llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)));

 //adding kappa comparison instructions
 //if(counttruth == count) //delete it
 //{
 llvm::IRBuilder<> builder3(assert);
 llvm::LoadInst *Load33 = builder3.CreateLoad(kappa);
 // llvm::Value *kappacheck = builder3.CreateICmpSLE(Load, IR.getInt32(0), "tmp");
 llvm::Value *kappacheck = builder3.CreateICmpNE(Load33, IR.getInt32(KappaValue), "tmp");

 llvm::BranchInst *kappaBr =  builder3.CreateCondBr(kappacheck,
 llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)), fail);
 // remove last BR
 //disable it later
 //llvm::Instruction *lastBR = kappaBr->getNextNode();
 //lastBR->removeFromParent();
 } //count-scope

 newblock->dump();   // new block
 //newBr->dump(); 		// current BR instruction
 previousBB = newblock;
 }else{
 previousBB = llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(2));
 //                                if(counttruth == count) //enable it later
 //                                {   //inserting the klee_assert instructions
 //                                    llvm::BasicBlock *assert = llvm::BasicBlock::Create(
 //                                        llvm::getGlobalContext(),"assert" , &F);
 //                                    llvm::BranchInst *Br = builder.CreateBr(assert);
 //                                    //new fail basic block
 //                                    llvm::BasicBlock *fail = llvm::BasicBlock::Create(
 //                                    llvm::getGlobalContext(),"fail" , &F);
 //                                    llvm::IRBuilder<> builder2(fail);
 //                                    //begin of klee_assert
 //                                    llvm::Constant *c = M->getOrInsertFunction("__assert_fail",
 //                                               llvm::FunctionType::getVoidTy(F.getContext()),
 //                                               llvm::Type::getInt8PtrTy(F.getContext()),
 //                                               llvm::Type::getInt8PtrTy(F.getContext()),
 //                                               llvm::IntegerType::get(llvm::getGlobalContext(),32),
 //                                               llvm::Type::getInt8PtrTy(F.getContext()),
 //                                               NULL);
 //                                    llvm::Function *assert_fail = llvm::dyn_cast<llvm::Function>(c);
 //                                    //IRBuilder<> builder(inst);
 //                                    llvm::Value *message = builder2.CreateGlobalStringPtr("kappa violation", ".str");
 //                                    llvm::Value *file = builder2.CreateGlobalStringPtr("", ".str");
 //                                    llvm::ConstantInt *line = builder2.getInt32(0);
 //                                    llvm::Value *function = builder2.CreateGlobalStringPtr("main", ".str");
 //                                    builder2.CreateCall4(assert_fail,message,file,line,function);
 //                                    //end of klee_assert
 //
 //                                    llvm::ReturnInst *retValue = builder2.CreateRet(IR.getInt32(-1));
 //
 //                                    //llvm::BranchInst *emptyBr = builder2.CreateBr(
 //                                    //        llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)));
 //
 //                                    //adding kappa comparison instructions
 //    			           //if(counttruth == count) //delete it
 //                                   //{
 //				   llvm::IRBuilder<> builder3(assert);
 //                                   llvm::LoadInst *Load33 = builder3.CreateLoad(kappa);
 //                                   // llvm::Value *kappacheck = builder3.CreateICmpSLE(Load, IR.getInt32(0), "tmp");
 //                                   llvm::Value *kappacheck = builder3.CreateICmpNE(Load33, IR.getInt32(KappaValue), "tmp");
 //
 //                                   llvm::BranchInst *kappaBr =  builder3.CreateCondBr(kappacheck,
 //                                   llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)), fail);
 //                                   // remove last BR
 //                                   //disable it later
 //                                   //llvm::Instruction *lastBR = kappaBr->getNextNode();
 //                                   //lastBR->removeFromParent();
 //                                } //count-scope

 }
 //print result in terminal
 bi->getOperand(2)->dump(); // true branch
 }
 }
 }

 } else {
 counttruth++;
 std::string buf;
 llvm::raw_string_ostream stream(buf);
 bi->getOperand(1)->print(stream);
 stream.flush();
 std::size_t s = buf.find('\n');
 if (s != std::string::npos) {
 if (s == 0) {
 buf = buf.substr(1, buf.size() - 1);
 s = buf.find('\n');
 if (s != std::string::npos) {
 std::string label = buf.substr(0, s);
 llvm::errs() << "SECOND BRANCH: " << label << "\n";
 llvm::IRBuilder<> IR(
 llvm::dyn_cast<llvm::BasicBlock>(
 bi->getOperand(1)));

 //inserting the store instruction for kappa variable
 if(counttruth == 1)
 {
 llvm::IRBuilder<> builder1(ins); // ins is for creating store instruction kappa = 0 in before icmp
 llvm::StoreInst *Store_zero = builder1.CreateStore(IR.getInt32(0), kappa);
 }

 // Reterieving destination block
 llvm::BasicBlock *tempblock;
 tempblock = llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1));


 // Add instructions to the new block //To check the new idea or else disable it
 //                            llvm::IRBuilder<> builder(tempblock);
 //                            llvm::LoadInst *Load = builder.CreateLoad(kappa);
 //                            llvm::Value *Inc = builder.CreateMul(IR.getInt32(10), Load);
 //                            llvm::StoreInst *Store = builder.CreateStore(Inc, kappa);
 //                            llvm::LoadInst *Load1 = builder.CreateLoad(kappa);
 //                            llvm::Value *Inc1 = builder.CreateAdd(IR.getInt32(2), Load1);
 //                            llvm::StoreInst *Store1 = builder.CreateStore(Inc1, kappa);
 //                            llvm::BranchInst *Br = builder.CreateBr(tempblock);

 KappaValue = (KappaValue * 10) + 2; // False to check the kappa value
 llvm::errs() << "here we are for FALSE\n" << label << "up to here for FALSE\n";

 size_t predPos = label.find("pred");
 label = label.substr( 0, predPos );
 llvm::errs() << "LABEL:" << label << "\n";
 if(label.find("kappa") == std::string::npos)
 {
 // Creating middle basic block for kappa increment
 std::ostringstream oss;
 oss << KappaValue;
 std::string newLabel = "kappa_";
 newLabel += oss.str();
 llvm::BasicBlock *newblock = llvm::BasicBlock::Create(llvm::getGlobalContext(),newLabel , &F);
 llvm::IRBuilder<> builder(newblock);
 llvm::errs() << "\n UWE ARE reaching here before\n ";

 //                                llvm::Type *i32_type = llvm::IntegerType::getInt32Ty(llvm::getGlobalContext());
 //                                llvm::Value *i32_val = llvm::ConstantInt::get(i32_type, KappaValue, false);
 //                                llvm::StoreInst *Store1 = builder.CreateStore(i32_val, kappa,false);
 //                                llvm::BranchInst *Br = builder.CreateBr(tempblock);

 llvm::LoadInst *Load = builder.CreateLoad(kappa);
 llvm::Value *Inc = builder.CreateMul(IR.getInt32(10), Load);
 llvm::StoreInst *Store = builder.CreateStore(Inc, kappa);
 llvm::LoadInst *Load1 = builder.CreateLoad(kappa);
 llvm::Value *Inc1 = builder.CreateAdd(IR.getInt32(2), Load1);
 llvm::StoreInst *Store1 = builder.CreateStore(Inc1, kappa);
 //                                if(icmpp[icmp+1]!=9)
 //                                {
 //                                //llvm::BranchInst *Br = builder.CreateBr(tempblock);
 //                                llvm::BranchInst *Br = builder.CreateBr(assert);
 //                                }
 //                                else
 //                                {
 //                                llvm::BranchInst *Br = builder.CreateBr(tempblock);
 //                                }



 if(icmpp[icmp+1]!=9 && counttruth != count)
 {
 llvm::BranchInst *Br = builder.CreateBr(tempblock);
 }
 else if(icmpp[icmp+1]!=9 && counttruth == count)   //enable it later
 {
 llvm::BasicBlock *assert = llvm::BasicBlock::Create(
 llvm::getGlobalContext(),"assert" , &F);
 llvm::BranchInst *Br = builder.CreateBr(assert);
 //new empty basic block
 llvm::BasicBlock *fail = llvm::BasicBlock::Create(
 llvm::getGlobalContext(),"fail" , &F);
 llvm::IRBuilder<> builder2(fail);

 //begin of klee_assert
 llvm::Constant *c = M->getOrInsertFunction("__assert_fail",
 llvm::FunctionType::getVoidTy(F.getContext()),
 llvm::Type::getInt8PtrTy(F.getContext()),
 llvm::Type::getInt8PtrTy(F.getContext()),
 llvm::IntegerType::get(llvm::getGlobalContext(),32),
 llvm::Type::getInt8PtrTy(F.getContext()),
 NULL);
 llvm::Function *assert_fail = llvm::dyn_cast<llvm::Function>(c);
 //IRBuilder<> builder(inst);
 llvm::Value *message = builder2.CreateGlobalStringPtr("kappa violation", ".str");
 llvm::Value *file = builder2.CreateGlobalStringPtr("", ".str");
 llvm::ConstantInt *line = builder2.getInt32(0);
 llvm::Value *function = builder2.CreateGlobalStringPtr("main", ".str");
 builder2.CreateCall4(assert_fail,message,file,line,function);
 //end of klee_assert
 llvm::ReturnInst *retValue = builder2.CreateRet(IR.getInt32(-1));
 //llvm::BranchInst *emptyBr = builder2.CreateBr(
 //     llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)));

 //adding kappa comparison instructions
 //if(counttruth == count) //delete it
 //{
 //llvm::BasicBlock *assert = llvm::BasicBlock::Create(
 //llvm::getGlobalContext(),"assert" , &F);

 llvm::IRBuilder<> builder3(assert);
 llvm::LoadInst *Load33 = builder3.CreateLoad(kappa);
 //llvm::Value *kappacheck = builder3.CreateICmpSLE(Load, IR.getInt32(0), "tmp");
 llvm::Value *kappacheck = builder3.CreateICmpNE(Load33, IR.getInt32(KappaValue), "tmp");
 llvm::BranchInst *kappaBr =  builder3.CreateCondBr(kappacheck,
 llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)), fail);

 // remove last BR
 //llvm::Instruction *lastBR = kappaBr->getNextNode();
 //lastBR->removeFromParent();
 // Calling klee_assert
 } //count-scope enable it later


 //newBr->dump(); 		// current BR instruction
 newblock->dump();   // new block
 previousBB = newblock;
 }else{
 // Creating middle basic block for kappa increment
 previousBB = llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1));
 //                                if(counttruth == count)   //enable it later
 //                                {
 //                                    llvm::BasicBlock *assert = llvm::BasicBlock::Create(
 //                                        llvm::getGlobalContext(),"assert" , &F);
 //                                    llvm::BranchInst *Br = builder.CreateBr(assert);
 //                                    //new empty basic block
 //                                    llvm::BasicBlock *fail = llvm::BasicBlock::Create(
 //                                        llvm::getGlobalContext(),"fail" , &F);
 //                                    llvm::IRBuilder<> builder2(fail);
 //
 //                                    //begin of klee_assert
 //                                    llvm::Constant *c = M->getOrInsertFunction("__assert_fail",
 //                                               llvm::FunctionType::getVoidTy(F.getContext()),
 //                                               llvm::Type::getInt8PtrTy(F.getContext()),
 //                                               llvm::Type::getInt8PtrTy(F.getContext()),
 //                                               llvm::IntegerType::get(llvm::getGlobalContext(),32),
 //                                               llvm::Type::getInt8PtrTy(F.getContext()),
 //                                               NULL);
 //                                    llvm::Function *assert_fail = llvm::dyn_cast<llvm::Function>(c);
 //                                    //IRBuilder<> builder(inst);
 //                                    llvm::Value *message = builder2.CreateGlobalStringPtr("kappa violation", ".str");
 //                                    llvm::Value *file = builder2.CreateGlobalStringPtr("", ".str");
 //                                    llvm::ConstantInt *line = builder2.getInt32(0);
 //                                    llvm::Value *function = builder2.CreateGlobalStringPtr("main", ".str");
 //                                    builder2.CreateCall4(assert_fail,message,file,line,function);
 //                                    //end of klee_assert
 //                                    llvm::ReturnInst *retValue = builder2.CreateRet(IR.getInt32(-1));
 //                                    //llvm::BranchInst *emptyBr = builder2.CreateBr(
 //                                    //     llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)));
 //
 //				   //adding kappa comparison instructions
 //				   //if(counttruth == count) //delete it
 //                                   //{
 //                                       //llvm::BasicBlock *assert = llvm::BasicBlock::Create(
 //                                        //llvm::getGlobalContext(),"assert" , &F);
 //
 //                                    llvm::IRBuilder<> builder3(assert);
 //                                    llvm::LoadInst *Load33 = builder3.CreateLoad(kappa);
 //                                    //llvm::Value *kappacheck = builder3.CreateICmpSLE(Load, IR.getInt32(0), "tmp");
 //                                    llvm::Value *kappacheck = builder3.CreateICmpNE(Load33, IR.getInt32(KappaValue), "tmp");
 //                                    llvm::BranchInst *kappaBr =  builder3.CreateCondBr(kappacheck,
 //                                    llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)), fail);
 //
 //				    // remove last BR
 //                                    //llvm::Instruction *lastBR = kappaBr->getNextNode();
 //                                    //lastBR->removeFromParent();
 //                                    // Calling klee_assert
 //                                } //count-scope enable it later
 }
 //print result in terminal
 bi->getOperand(2)->dump(); // true branch
 }
 }
 }
 }
 } else {
 //newly added for dont care
 llvm::errs() << "ICSE\n";
 previousBB->dump();
 llvm::errs() << "ICSE\n";
 ////////////////////////////////////////////////////////
 // TODO: REMOVE BR AND ADD INSTRUCTIONS AND THEN ADD BR
 ////////////////////////////////////////////////////////

 KappaValue = (KappaValue * 10) + 0; // False
 llvm::errs() << "Entered condition value is don't care\n";
 llvm::IRBuilder<> builder5(previousBB);
 llvm::IRBuilder<> IR(llvm::dyn_cast<llvm::BasicBlock>(previousBB));
 llvm::LoadInst *Load = builder5.CreateLoad(kappa);
 llvm::Value *Inc = builder5.CreateMul(IR.getInt32(10), Load);
 llvm::StoreInst *Store = builder5.CreateStore(Inc, kappa);

 if(counttruth == count)
 {llvm::BasicBlock *assert = llvm::BasicBlock::Create(
 llvm::getGlobalContext(),"assert" , &F);
 llvm::BranchInst *Br = builder5.CreateBr(assert);
 //new empty basic block
 llvm::BasicBlock *fail = llvm::BasicBlock::Create(
 llvm::getGlobalContext(),"fail" , &F);
 llvm::IRBuilder<> builder2(fail);

 //begin of klee_assert
 llvm::Constant *c = M->getOrInsertFunction("__assert_fail",
 llvm::FunctionType::getVoidTy(F.getContext()),
 llvm::Type::getInt8PtrTy(F.getContext()),
 llvm::Type::getInt8PtrTy(F.getContext()),
 llvm::IntegerType::get(llvm::getGlobalContext(),32),
 llvm::Type::getInt8PtrTy(F.getContext()),
 NULL);
 llvm::Function *assert_fail = llvm::dyn_cast<llvm::Function>(c);
 //IRBuilder<> builder(inst);
 llvm::Value *message = builder2.CreateGlobalStringPtr("kappa violation", ".str");
 llvm::Value *file = builder2.CreateGlobalStringPtr("", ".str");
 llvm::ConstantInt *line = builder2.getInt32(0);
 llvm::Value *function = builder2.CreateGlobalStringPtr("main", ".str");
 builder2.CreateCall4(assert_fail,message,file,line,function);
 //end of klee_assert
 llvm::ReturnInst *retValue = builder2.CreateRet(IR.getInt32(-1));
 //llvm::BranchInst *emptyBr = builder2.CreateBr(
 //        llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)));

 //adding kappa comparison instructions
 //if(counttruth == count) //delete it
 //{
 //llvm::BasicBlock *assert = llvm::BasicBlock::Create(
 //llvm::getGlobalContext(),"assert" , &F);

 llvm::IRBuilder<> builder3(assert);
 llvm::LoadInst *Load33 = builder3.CreateLoad(kappa);
 //llvm::Value *kappacheck = builder3.CreateICmpSLE(Load, IR.getInt32(0), "tmp");
 llvm::Value *kappacheck = builder3.CreateICmpNE(Load33, IR.getInt32(KappaValue), "tmp");
 llvm::BranchInst *kappaBr =  builder3.CreateCondBr(kappacheck,
 llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)), fail);

 // remove last BR
 //llvm::Instruction *lastBR = kappaBr->getNextNode();
 //lastBR->removeFromParent();
 // Calling klee_assert
 }
 else if(icmpp[icmp-1] = 1)
 {
 llvm::BranchInst *Br1 = builder5.CreateBr(llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(1)));
 }
 else if(icmpp[icmp-1] = 0)
 {
 llvm::BranchInst *Br1 = builder5.CreateBr(llvm::dyn_cast<llvm::BasicBlock>(bi->getOperand(2)));
 }




 // remove last BR
 //llvm::Instruction *lastBR = Br->getNextNode();
 //lastBR->removeFromParent();
 //llvm::BranchInst *newBr = llvm::BranchInst::Create(previousBB);
 //b->getInstList().insertAfter(bi,llvm::dyn_cast<llvm::Instruction>(newBr));
 //bi->removeFromParent();
 }
 }
 }
 } else {
 llvm::errs() << "No next node\n";
 }
 }
 }*/

