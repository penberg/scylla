/*
 * Copyright 2019 ScyllaDB
 */

/*
 * This file is part of Scylla.
 *
 * Scylla is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Scylla is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Scylla.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <seastar/core/future.hh>
#include <seastar/http/httpd.hh>
#include "seastarx.hh"
#include <seastar/json/json_elements.hh>
#include <seastar/core/sharded.hh>

#include "service/storage_proxy.hh"
#include "service/migration_manager.hh"
#include "service/client_state.hh"

#include "alternator/error.hh"
#include "stats.hh"

namespace alternator {

class executor : public peering_sharded_service<executor> {
    service::storage_proxy& _proxy;
    service::migration_manager& _mm;

public:
    using client_state = service::client_state;
    using request_return_type = std::variant<json::json_return_type, api_error>;
    stats _stats;
    static constexpr auto ATTRS_COLUMN_NAME = ":attrs";
    static constexpr auto KEYSPACE_NAME_PREFIX = "a#";

    executor(service::storage_proxy& proxy, service::migration_manager& mm) : _proxy(proxy), _mm(mm) {}

    future<request_return_type> create_table(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> describe_table(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> delete_table(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> put_item(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> get_item(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> delete_item(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> update_item(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> list_tables(client_state& client_state, std::string content);
    future<request_return_type> scan(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> describe_endpoints(client_state& client_state, std::string content, std::string host_header);
    future<request_return_type> batch_write_item(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> batch_get_item(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> query(client_state& client_state, tracing::trace_state_ptr trace_state, std::string content);
    future<request_return_type> tag_resource(client_state& client_state, std::string content);
    future<request_return_type> untag_resource(client_state& client_state, std::string content);
    future<request_return_type> list_tags_of_resource(client_state& client_state, std::string content);

    future<> start();
    future<> stop() { return make_ready_future<>(); }

    future<> create_keyspace(std::string_view keyspace_name);

    static tracing::trace_state_ptr maybe_trace_query(client_state& client_state, sstring_view op, sstring_view query);
};

}
