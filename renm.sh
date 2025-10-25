#!/bin/bash
# 遍历当前目录及子目录下所有包含"_new"的文件
find . -type f -name "*_new*" | while read -r file; do
    # 获取文件所在目录和基本名
    dir=$(dirname "$file")
    base=$(basename "$file")
    
    # 替换_new为空字符串
    newbase=${base//_new/}
    
    # 避免同名文件覆盖
    if [ "$base" != "$newbase" ]; then
        mv -i "$file" "$dir/$newbase"
        echo "Renamed: $file -> $dir/$newbase"
    fi
done
