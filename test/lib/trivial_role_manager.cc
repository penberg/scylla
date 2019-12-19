/*
 * Copyright (C) 2019 ScyllaDB
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
 * You should have received a copy of the GNU General Public License
 * along with Scylla.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "test/lib/trivial_role_manager.hh"

#include "cql3/query_processor.hh"

static const class_registrator<
        auth::role_manager,
	trivial_role_manager,
	cql3::query_processor&,
	::service::migration_manager&> registration("org.apache.cassandra.auth.TrivialRoleManager");

trivial_role_manager::trivial_role_manager(cql3::query_processor& qp, ::service::migration_manager& mm)
{
}

std::string_view trivial_role_manager::qualified_java_name() const noexcept {
    return "org.apache.cassandra.auth.TrivialRoleManager";
}

const auth::resource_set& trivial_role_manager::protected_resources() const {
    static const auth::resource_set resources{};
    return resources;
}

future<> trivial_role_manager::start() {
    return make_ready_future<>();
}

future<> trivial_role_manager::stop() {
    return make_ready_future<>();
}

future<> trivial_role_manager::create(std::string_view role_name, const auth::role_config&) const {
    bool inserted;
    std::tie(std::ignore, inserted) = _roles.insert(std::string(role_name));
    if (!inserted) {
        throw auth::role_already_exists(role_name);
    }
    return make_ready_future<>();
}

future<> trivial_role_manager::drop(std::string_view role_name) const {
    auto it = _roles.find(std::string(role_name));
    if (it == _roles.end()) {
        throw auth::nonexistant_role(role_name);
    }
    _roles.erase(it);
    return make_ready_future<>();
}

future<> trivial_role_manager::alter(std::string_view role_name, const auth::role_config_update&) const {
    return make_ready_future<>();
}

future<> trivial_role_manager::grant(std::string_view grantee_name, std::string_view role_name) const {
    return make_ready_future<>();
}

future<> trivial_role_manager::revoke(std::string_view revokee_name, std::string_view role_name) const {
    return make_ready_future<>();
}

future<auth::role_set> trivial_role_manager::query_granted(std::string_view grantee_name, auth::recursive_role_query) const {
    return make_ready_future<auth::role_set>(_roles);
}

future<auth::role_set> trivial_role_manager::query_all() const {
    return make_ready_future<auth::role_set>(_roles);
}

future<bool> trivial_role_manager::exists(std::string_view role_name) const {
    bool exists = _roles.count(std::string(role_name)) > 0;
    return make_ready_future<bool>(exists);
}

future<bool> trivial_role_manager::is_superuser(std::string_view role_name) const {
    return make_ready_future<bool>(true);
}

future<bool> trivial_role_manager::can_login(std::string_view role_name) const {
    return exists(role_name);
}
