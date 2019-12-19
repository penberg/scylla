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

#pragma once

#include "auth/role_manager.hh"

namespace cql3 {
    class query_processor;
}

namespace service {
    class migration_manager;
}

/// A trivial role manager implementation that does not use the database to
/// manage roles. Used for ensuring isolation in CQL unit tests.
class trivial_role_manager final : public auth::role_manager {

    mutable auth::role_set _roles; // mutable because role manager interface is const.

public:
    trivial_role_manager(cql3::query_processor& qp, ::service::migration_manager& mm);

    virtual std::string_view qualified_java_name() const noexcept override;

    virtual const auth::resource_set& protected_resources() const override;

    virtual future<> start() override;

    virtual future<> stop() override;

    virtual future<> create(std::string_view role_name, const auth::role_config&) const override;

    virtual future<> drop(std::string_view role_name) const override;

    virtual future<> alter(std::string_view role_name, const auth::role_config_update&) const override;

    virtual future<> grant(std::string_view grantee_name, std::string_view role_name) const override;

    virtual future<> revoke(std::string_view revokee_name, std::string_view role_name) const override;

    virtual future<auth::role_set> query_granted(std::string_view grantee_name, auth::recursive_role_query) const override;

    virtual future<auth::role_set> query_all() const override;

    virtual future<bool> exists(std::string_view role_name) const override;

    virtual future<bool> is_superuser(std::string_view role_name) const override;

    virtual future<bool> can_login(std::string_view role_name) const override;
};
