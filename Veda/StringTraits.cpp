#include "stdafx.h"
#include "StringTraits.h"
namespace veda
{
	const CharTraits::value_type* CharTraits::_intFormat = "%d";
	const CharTraits::value_type* CharTraits::_uIntFormat = "%u";
	const CharTraits::value_type* CharTraits::_lIntFormat = "%ld";
	const CharTraits::value_type* CharTraits::_floatFormat = "%f";
	const CharTraits::value_type* CharTraits::_lFloatFormat = "%lf";

	const WcharTraits::value_type* WcharTraits::_intFormat = L"%d";
	const WcharTraits::value_type* WcharTraits::_uIntFormat = L"%u";
	const WcharTraits::value_type* WcharTraits::_lIntFormat = L"%ld";
	const WcharTraits::value_type* WcharTraits::_floatFormat = L"%f";
	const WcharTraits::value_type* WcharTraits::_lFloatFormat = L"%lf";
}