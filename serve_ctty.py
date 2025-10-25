#!/usr/bin/env python3
"""Serve CTty.tar.gz over HTTP for easy local downloads."""
from __future__ import annotations

import argparse
import http.server
import sys
import threading
import webbrowser
from functools import partial
from pathlib import Path


def positive_int(value: str) -> int:
    try:
        port = int(value)
    except ValueError as exc:
        raise argparse.ArgumentTypeError("端口号必须是整数") from exc
    if not (0 <= port <= 65535):
        raise argparse.ArgumentTypeError("端口号必须在 0-65535 之间")
    return port


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="启动一个本地 HTTP 服务，直接提供 CTty.tar.gz 下载链接。"
    )
    parser.add_argument(
        "--port",
        type=positive_int,
        default=0,
        help="监听端口，默认 0 表示自动选择空闲端口。",
    )
    parser.add_argument(
        "--bind",
        default="127.0.0.1",
        help="绑定地址，默认仅本机可访问。",
    )
    parser.add_argument(
        "--open",
        action="store_true",
        help="启动后自动在浏览器中打开下载链接。",
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=Path(__file__).resolve().parent,
        help="要共享的目录，默认是脚本所在目录。",
    )
    return parser


def normalise_host(host: str) -> str:
    if host in {"", "0.0.0.0"}:
        return "127.0.0.1"
    return host


def serve(root: Path, host: str, port: int, open_browser: bool) -> None:
    archive = root / "CTty.tar.gz"
    if not archive.exists():
        sys.stderr.write(f"未找到归档文件: {archive}\n")
        sys.exit(1)

    handler = partial(http.server.SimpleHTTPRequestHandler, directory=str(root))
    server = http.server.ThreadingHTTPServer((host, port), handler, bind_and_activate=False)

    with server:
        try:
            server.server_bind()
            server.server_activate()
        except OSError as exc:
            sys.stderr.write(f"启动服务失败: {exc}\n")
            sys.exit(1)

        bound_host, bound_port = server.server_address
        display_host = normalise_host(bound_host)
        url = f"http://{display_host}:{bound_port}/CTty.tar.gz"
        print("==============================")
        print("CTty.tar.gz 本地下载链接")
        print("==============================")
        print(url)
        print("按 Ctrl+C 可停止服务。")
        if open_browser:
            threading.Thread(target=webbrowser.open, args=(url,), daemon=True).start()

        try:
            server.serve_forever()
        except KeyboardInterrupt:
            print("\n服务已停止。")


def main() -> None:
    parser = build_parser()
    args = parser.parse_args()
    serve(args.root.resolve(), args.bind, args.port, args.open)


if __name__ == "__main__":
    main()
