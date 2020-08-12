{
  "targets": [
    {
      "target_name": "DisplayManager",
      "sources": [ "addon.cc", "DisplayManager.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
