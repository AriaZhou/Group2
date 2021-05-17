// Copyright (c) 2021 Pei-Ru Wang, Cheryl Huang, Yuan Zhou. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/**
 * Project MyHttpServer
 * @author Pei-Ru Wang, Cheryl Huang, Yuan Zhou
 * @version 0.0.1
 */

#include "HttpRequestHandler.h"

#include "HttpRequestPacket.h"
#include "HttpResponsePacket.h"

/**
 * HttpRequestHandler implementation
 */

HttpRequestHandler::HttpRequestHandler(
    boost::asio::io_service &io_service,
    std::unordered_map<int, handler_ptr> &map_handler_list, int n_count)
    : map_handler_list(map_handler_list), n_count(n_count),
      HttpHandler(io_service) {}

HttpRequestHandler::~HttpRequestHandler() {
  HttpRequestHandler::Stop();
  std::cout << n_count << ":~HandlerComplete" << std::endl;
}

void HttpRequestHandler::Start() {
  auto self(shared_from_this());
  map_handler_list.insert(std::make_pair(n_count, self));

  HttpRequestHandler::HandleRead();
}

void HttpRequestHandler::Stop() {
  auto it = map_handler_list.find(n_count);
  map_handler_list.erase(it);
  socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
  socket.close();
}

void HttpRequestHandler::HandleRead() {
  auto self(shared_from_this());
  socket.async_read_some(
      boost::asio::buffer(buffer),
      strand.wrap(
          [this, self](std::error_code error, std::size_t bytes_transferred) {
            if (!error) {
              HttpRequestPacket::parse_result result;
              std::tie(result, std::ignore) = httpRequestPacket.ParseBytes(
                  buffer.data(), buffer.data() + bytes_transferred);

              if (result == HttpRequestPacket::success) {
                httpRouterHandler.RouteHttpRequest(httpRequestPacket,
                                                   httpResponsePacket);
                HttpRequestHandler::HandleWrite();
              } else if (result == HttpRequestPacket::success) {

                HttpRequestHandler::HandleWrite();
              } else {
                HttpRequestHandler::HandleRead();
              }
            }
          }));
}

void HttpRequestHandler::HandleWrite() {}
