// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// Copyright 2019 FZI Forschungszentrum Informatik (ur_robot_driver)
// Copyright 2017, 2018 Simon Rasmussen (refactor)
//
// Copyright 2015, 2016 Thomas Timm Andersen (original version)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Felix Exner exner@fzi.de
 * \date    2020-04-30
 *
 */
//----------------------------------------------------------------------

#include "ur_client_library/primary/robot_message/error_code_message.h"
#include "ur_client_library/primary/abstract_primary_consumer.h"

namespace urcl
{
namespace primary_interface
{
ErrorCodeMessage::ErrorCodeMessage(const ErrorCodeMessage& pkg)
  : RobotMessage(pkg.timestamp_, pkg.source_, RobotMessagePackageType::ROBOT_MESSAGE_ERROR_CODE)
{
  message_code_ = pkg.message_code_;
  message_argument_ = pkg.message_argument_;
  report_level_ = pkg.report_level_;
  data_type_ = pkg.data_type_;
  data_ = pkg.data_;
  text_ = pkg.text_;
}

bool ErrorCodeMessage::parseWith(comm::BinParser& bp)
{
  bp.parse(message_code_);
  bp.parse(message_argument_);
  int32_t report_level;
  bp.parse(report_level);
  report_level_ = static_cast<ReportLevel>(report_level);
  bp.parse(data_type_);
  bp.parse(data_);
  bp.parseRemainder(text_);

  return true;  // not really possible to check dynamic size packets
}

bool ErrorCodeMessage::consumeWith(AbstractPrimaryConsumer& consumer)
{
  return consumer.consume(*this);
}

std::string ErrorCodeMessage::toString() const
{
  std::stringstream ss;
  ss << "Message code: " << message_code_ << std::endl;
  ss << "Message argument: " << message_argument_ << std::endl;
  ss << "Report level: " << static_cast<int>(report_level_) << std::endl;
  ss << "Datatype: " << static_cast<int>(data_type_) << std::endl;
  ss << "Data: " << data_ << std::endl;
  ss << "Text: " << text_;
  return ss.str();
}
}  // namespace primary_interface
}  // namespace urcl
