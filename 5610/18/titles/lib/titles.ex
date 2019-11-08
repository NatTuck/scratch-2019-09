defmodule Titles do
  def reddit_list(sub) do
    resp = HTTPoison.get!("https://www.reddit.com/r/#{sub}.json")
    data = Jason.decode!(resp.body)
    data["data"]["children"]
  end

  def list_titles(sub) do
    xs = reddit_list(sub)
    Enum.map xs, fn x ->
      x["data"]["title"]
    end
  end
end
