/*
  Commands.h
  Интерфейс команд языка
*/ 

#pragma once 
#include "interface.h"

class CmdExpression final : public Command {
public: 
  virtual bool Process(Parser&);
};

class CmdPrint final : public Command {
public: 
  virtual bool Process(Parser&);
};

class CmdInput final : public Command {
public: 
  virtual bool Process(Parser&);
};

class CmdFor final : public Command {
public: 
  virtual bool Process(Parser&);
};

class CmdNext final : public Command {
public: 
  virtual bool Process(Parser&);
};

class CmdGoto final : public Command {
public: 
  virtual bool Process(Parser&);
};

class CmdIf final : public Command {
public: 
  virtual bool Process(Parser&);
};