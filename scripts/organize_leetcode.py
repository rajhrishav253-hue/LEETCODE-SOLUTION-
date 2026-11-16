#!/usr/bin/env python3
"""Move LeetSync-created problem folders into topic folders using LeetCode tags."""
import json
import re
import subprocess
import sys
import time
from pathlib import Path

import requests

ROOT = Path(".")
GRAPHQL_URL = "https://leetcode.com/graphql"
HEADERS = {
    "Content-Type": "application/json",
    "Referer": "https://leetcode.com/",
    "User-Agent": "Mozilla/5.0 (compatible; LeetCodeTopicOrganizer/1.0)",
}

# Prefer the most useful primary study topic when a problem has several tags.
TOPIC_MAP = {
    "array": "ARRAY",
    "string": "STRING",
    "binary search": "BINARY SEARCH",
    "linked list": "Linked List",
    "stack": "STACK",
    "queue": "QUEUE",
    "tree": "BINARY TREE",
    "binary tree": "BINARY TREE",
    "graph": "GRAPH",
    "dynamic programming": "DYNAMIC PROGRAMMING ",
    "greedy": "GREEDY",
    "heap (priority queue)": "HEAP",
    "heap": "HEAP",
    "hash table": "HASH TABLE",
    "math": "MATH",
}
PRIORITY = [
    "array", "string", "binary search", "linked list", "stack", "queue",
    "tree", "binary tree", "graph", "dynamic programming", "greedy",
    "heap (priority queue)", "heap", "hash table", "math",
]

def leetcode_tags(slug: str):
    query = """
    query questionTopics($titleSlug: String!) {
      question(titleSlug: $titleSlug) {
        topicTags { name slug }
      }
    }
    """
    response = requests.post(
        GRAPHQL_URL,
        headers=HEADERS,
        json={"query": query, "variables": {"titleSlug": slug}},
        timeout=25,
    )
    response.raise_for_status()
    payload = response.json()
    question = payload.get("data", {}).get("question")
    if not question:
        raise ValueError(f"LeetCode returned no question for slug: {slug}")
    return [tag["name"].strip().lower() for tag in question.get("topicTags", [])]

def git_move(source: Path, destination: Path):
    destination.parent.mkdir(parents=True, exist_ok=True)
    if destination.exists():
        print(f"SKIP (destination already exists): {destination}")
        return False
    subprocess.run(["git", "mv", str(source), str(destination)], check=True)
    print(f"MOVED: {source} -> {destination}")
    return True

def main():
    candidates = []
    for path in ROOT.iterdir():
        if not path.is_dir() or path.name.startswith("."):
            continue
        # LeetSync's default problem directory format: 0001-two-sum
        match = re.match(r"^\d{1,5}-(.+)$", path.name)
        if match and any(path.glob("*.cpp")):
            candidates.append((path, match.group(1)))

    if not candidates:
        print("No unorganized LeetSync C++ problem folders found.")
        return

    moved = 0
    for folder, slug in sorted(candidates):
        try:
            tags = leetcode_tags(slug)
            category = next(
                (TOPIC_MAP[tag] for tag in PRIORITY if tag in tags),
                "OTHER",
            )
            target = Path(category) / folder.name
            if git_move(folder, target):
                moved += 1
            time.sleep(0.5)
        except Exception as exc:
            print(f"WARNING: Could not organize {folder.name}: {exc}", file=sys.stderr)

    if moved:
        subprocess.run(
            ["git", "config", "user.name", "github-actions[bot]"],
            check=True,
        )
        subprocess.run(
            ["git", "config", "user.email", "41898282+github-actions[bot]@users.noreply.github.com"],
            check=True,
        )
        subprocess.run(["git", "commit", "-m", f"Organize {moved} LeetCode solution(s) by topic"], check=True)
        subprocess.run(["git", "push"], check=True)
    else:
        print("No folders were moved.")

if __name__ == "__main__":
    main()
