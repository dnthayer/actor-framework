/******************************************************************************
 *                       ____    _    _____                                   *
 *                      / ___|  / \  |  ___|    C++                           *
 *                     | |     / _ \ | |_       Actor                         *
 *                     | |___ / ___ \|  _|      Framework                     *
 *                      \____/_/   \_|_|                                      *
 *                                                                            *
 * Copyright (C) 2011 - 2015                                                  *
 * Dominik Charousset <dominik.charousset (at) haw-hamburg.de>                *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 *                                                                            *
 * If you did not receive a copy of the license files, see                    *
 * http://opensource.org/licenses/BSD-3-Clause and                            *
 * http://www.boost.org/LICENSE_1_0.txt.                                      *
 ******************************************************************************/

#include "caf/io/hook.hpp"

#include "caf/message_id.hpp"

namespace caf {
namespace io {

hook::~hook() {
  // nop
}

void hook::message_received_cb(const node_id& source,
                               const strong_actor_ptr& from,
                               const strong_actor_ptr& dest, message_id mid,
                               const message& msg) {
  call_next<message_received>(source, from, dest, mid, msg);
}

void hook::message_sent_cb(const strong_actor_ptr& from, const node_id& dest_node,
                           const strong_actor_ptr& dest, message_id mid,
                           const message& payload) {
  call_next<message_sent>(from, dest_node, dest, mid, payload);
}

void hook::message_forwarded_cb(const basp::header& hdr,
                                const std::vector<char>* payload) {
  call_next<message_forwarded>(hdr, payload);
}

void hook::message_forwarding_failed_cb(const basp::header& hdr,
                                        const std::vector<char>* payload) {
  call_next<message_forwarding_failed>(hdr, payload);
}

void hook::message_sending_failed_cb(const strong_actor_ptr& from,
                                     const strong_actor_ptr& dest,
                                     message_id mid,
                                     const message& payload) {
  call_next<message_sending_failed>(from, dest, mid, payload);
}

void hook::actor_published_cb(const strong_actor_ptr& addr,
                              const std::set<std::string>& ifs,
                              uint16_t port) {
  call_next<actor_published>(addr, ifs, port);
}

void hook::new_remote_actor_cb(const strong_actor_ptr& addr) {
  call_next<new_remote_actor>(addr);
}

void hook::new_connection_established_cb(const node_id& node) {
  call_next<new_connection_established>(node);
}

void hook::new_route_added_cb(const node_id& via, const node_id& node) {
  call_next<new_route_added>(via, node);
}

void hook::connection_lost_cb(const node_id& dest) {
  call_next<connection_lost>(dest);
}

void hook::route_lost_cb(const node_id& hop, const node_id& dest) {
  call_next<route_lost>(hop, dest);
}

void hook::invalid_message_received_cb(const node_id& source,
                                       const strong_actor_ptr& sender,
                                       actor_id invalid_dest,
                                       message_id mid,
                                       const message& msg) {
  call_next<invalid_message_received>(source, sender, invalid_dest, mid, msg);
}

void hook::before_shutdown_cb() {
  call_next<before_shutdown>();
}

} // namespace io
} // namespace caf
