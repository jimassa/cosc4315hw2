#include <mypython/term.hpp>

#include <util/variant.hpp>

namespace MyPython {
// Non-matching functions.
namespace {
template <class T1, class T2>
auto cmp(T1 const& a, T2 const& b) -> int {
  throw "Error comparing two types";
}

template <class T>
auto str(T const&) -> Str {
  throw "Error converting to str";
}

template <class T>
auto truth_value(T const&) -> bool {
  throw "No truth value exists";
}

template <class T1, class T2>
auto add(T1 const& a, T2 const& b) -> Term {
  throw "Cannot add two types";
}

template <class T1, class T2>
auto sub(T1 const& a, T2 const& b) -> Term {
  throw "Cannot add sub types";
}

template <class T1, class T2>
auto mul(T1 const& a, T2 const& b) -> Term {
  throw "Cannot mul two types";
}

template <class T1, class T2>
auto div(T1 const& a, T2 const& b) -> Term {
  throw "Cannot div two types";
}
}  // namespace

auto cmp(Term const& a, Term const& b) -> int {
  auto visitor = [](auto&& a, auto&& b) { return cmp(a, b); };
  return mpark::visit(visitor, a, b);
}

auto str(Term const& term) -> Str {
  auto visitor = [](auto&& term) { return str(term); };
  return mpark::visit(visitor, term);
}

auto truth_value(Term const& term) -> bool {
  auto visitor = [](auto&& term) { return truth_value(term); };
  return mpark::visit(visitor, term);
}

auto add(Term const& a, Term const& b) -> Term {
  auto visitor = [](auto&& a, auto&& b) { return add(a, b); };
  return mpark::visit(visitor, a, b);
}

auto sub(Term const& a, Term const& b) -> Term {
  auto visitor = [](auto&& a, auto&& b) { return sub(a, b); };
  return mpark::visit(visitor, a, b);
}

auto mul(Term const& a, Term const& b) -> Term {
  auto visitor = [](auto&& a, auto&& b) { return mul(a, b); };
  return mpark::visit(visitor, a, b);
}

auto div(Term const& a, Term const& b) -> Term {
  auto visitor = [](auto&& a, auto&& b) { return div(a, b); };
  return mpark::visit(visitor, a, b);
}

auto cmp(Str const& a, Str const& b) -> int { return a.value.compare(b.value); }

auto str(Str const& str) -> Str { return str; }
auto truth_value(Str const& str) -> bool { return !str.value.empty(); }

auto add(Str const& a, Str const& b) -> Term { return Str(a.value + b.value); }
auto mul(Str const& a, Int const& b) -> Term {
  Str result;
  for (int i = 0; i < b.value; ++i) {
    result.value += a.value;
  }
  return result;
}

auto cmp(Int const& a, Int const& b) -> int {
  if (a.value < b.value)
    return -1;
  else if (a.value > b.value)
    return 1;
  else
    return 0;
}

auto str(Int const& i) -> Str { return Str(std::to_string(i.value)); }
auto truth_value(Int const& i) -> bool { return i.value != 0; }

auto add(Int const& a, Int const& b) -> Term { return Int(a.value + b.value); }
auto sub(Int const& a, Int const& b) -> Term { return Int(a.value - b.value); }
auto mul(Int const& a, Int const& b) -> Term { return Int(a.value * b.value); }
auto div(Int const& a, Int const& b) -> Term { return Int(a.value / b.value); }

auto str(Bool const& b) -> Str {
  if (b.value != 0) {
    return Str("True");
  } else {
    return Str("False");
  }
}

auto str(NoneType const& n) -> Str { return Str("None"); }

////
}  // namespace MyPython