#ifndef __L22_TARGETS_SYMBOL_H__
#define __L22_TARGETS_SYMBOL_H__

#include <string>
#include <memory>
#include <cdk/types/basic_type.h>

namespace l22
{

  class symbol
  {
    std::shared_ptr<cdk::basic_type> _type;
    std::string _name;
    int _qualifier;
    int _offset = 0; // 0 means global variable

  public:
    symbol(std::shared_ptr<cdk::basic_type> type, const std::string &name, int qualifier) : _type(type), _name(name), _qualifier(qualifier)
    {
    }

    virtual ~symbol()
    {
      // EMPTY
    }

    std::shared_ptr<cdk::basic_type> type() const
    {
      return _type;
    }
    bool is_typed(cdk::typename_type name) const
    {
      return _type->name() == name;
    }
    const std::string &name() const
    {
      return _name;
    }
    int offset() const
    {
      return _offset;
    }
    int set_offset(int offset)
    {
      return _offset = offset;
    }
    int qualifier() const
    {
      return _qualifier;
    }
    bool global() const
    {
      return _offset == 0;
    }
  };

  inline auto make_symbol(std::shared_ptr<cdk::basic_type> type, const std::string &name, int qualifier)
  {
    return std::make_shared<symbol>(type, name, qualifier);
  }

} // l22

#endif
