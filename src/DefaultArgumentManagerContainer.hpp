//
//  DefaultArgumentManagerContainer.hpp
//  integral
//
//  Copyright (C) 2016, 2017  André Pereira Henriques
//  aphenriques (at) outlook (dot) com
//
//  This file is part of integral.
//
//  integral is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  integral is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with integral.  If not, see <http://www.gnu.org/licenses/>.
//


#ifndef integral_DefaultArgumentManagerContainer_hpp
#define integral_DefaultArgumentManagerContainer_hpp

#include <cstddef>
#include <utility>
#include "argument.hpp"
#include "DefaultArgumentManager.hpp"
#include "IsTemplateClass.hpp"

namespace integral {
    namespace detail {
        template<typename T, typename ...A>
        class DefaultArgumentManagerContainer {
            static_assert(IsTemplateClass<DefaultArgumentManager, T>::value == true, "typename T in DefaultArgumentManagerContainer must be a DefaultArgumentManager");
        public:
            template<typename ...E, std::size_t ...I>
            inline DefaultArgumentManagerContainer(DefaultArgument<E, I> &&...defaultArguments);

            inline const T & getDefaultArgumentManager() const;

        private:
            T defaultArgumentManager_;
        };

        //--

        template<typename T, typename ...A>
        template<typename ...E, std::size_t ...I>
        inline DefaultArgumentManagerContainer<T, A...>::DefaultArgumentManagerContainer(DefaultArgument<E, I> &&...defaultArguments) : defaultArgumentManager_(std::move(defaultArguments)...) {
            argument::validateDefaultArguments<A...>(defaultArguments...);
        }

        template<typename T, typename ...A>
        inline const T & DefaultArgumentManagerContainer<T, A...>::getDefaultArgumentManager() const {
            return defaultArgumentManager_;
        }
    }
}

#endif /* integral_DefaultArgumentManagerContainer_hpp */
